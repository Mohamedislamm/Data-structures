package invertedIndex;

import org.jsoup.Jsoup;
import org.jsoup.Connection;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import javax.net.ssl.*;
import java.security.cert.X509Certificate;

public class Crawler {
    private static final int MAX_PAGES = 10;
    private static final String CORPUS_DIR = "data/corpus";
    private final Set<String> visitedUrls = new LinkedHashSet<>();

    static {
        try {
            TrustManager[] trustAllCerts = new TrustManager[]{
                new X509TrustManager() {
                    public X509Certificate[] getAcceptedIssuers() { return null; }
                    public void checkClientTrusted(X509Certificate[] certs, String authType) { }
                    public void checkServerTrusted(X509Certificate[] certs, String authType) { }
                }
            };
            SSLContext sc = SSLContext.getInstance("SSL");
            sc.init(null, trustAllCerts, new java.security.SecureRandom());
            HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
            HttpsURLConnection.setDefaultHostnameVerifier((hostname, session) -> true);
        } catch (Exception e) {
        }
    }

    public void crawl(String seedUrl) {
        processPage(seedUrl);
    }

    public List<String> getVisitedUrls() {
        return new ArrayList<>(visitedUrls);
    }

    private void processPage(String url) {
        if (visitedUrls.size() >= MAX_PAGES || visitedUrls.contains(url)) return;

        try {
            Connection conn = Jsoup.connect(url);
            conn.userAgent("Mozilla/5.0");
            conn.referrer("https://www.google.com/");
            conn.header("Accept-Language", "en-US,en;q=0.9");
            conn.timeout(30000);
            conn.ignoreHttpErrors(true);
            conn.ignoreContentType(true);
            conn.followRedirects(true);
            
            Document doc = conn.get();

            visitedUrls.add(url);

            new java.io.File(CORPUS_DIR).mkdirs();
            String fileName = CORPUS_DIR + "/doc" + visitedUrls.size() + ".txt";
            FileWriter writer = new FileWriter(fileName);
            writer.write(doc.text());
            writer.close();

            System.out.println("Crawled [" + visitedUrls.size() + "]: " + url);

          
              Elements links = doc.select("a[href^=\"/wiki/\"]");

              for (Element link : links) {

                  String nextUrl = link.absUrl("href");

                  if (nextUrl.startsWith("https://en.m.wikipedia.org/")) {
                      nextUrl = nextUrl.replace(
                          "https://en.m.wikipedia.org/",
                          "https://en.wikipedia.org/"
                      );
                  }

                  if (!nextUrl.startsWith("https://en.wikipedia.org/wiki/"))
                      continue;

                  // نفحص فقط اسم الصفحة بعد /wiki/
                  String path = nextUrl.substring(
                      "https://en.wikipedia.org/wiki/".length()
                  );

                  // استبعاد صفحات مثل Category: أو File:
                  if (path.contains(":"))
                      continue;

                  if (!visitedUrls.contains(nextUrl)
                          && visitedUrls.size() < MAX_PAGES) {

                      processPage(nextUrl);
                  }
              }
        } catch (IOException e) {
            System.err.println("Error: " + url + " (" + e.getMessage() + ")");
        }
    }
}