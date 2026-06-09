package invertedIndex;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.File;
import java.util.*;

public class Test {

    private static void disableSSLCertificateChecking() {
        try {
            javax.net.ssl.TrustManager[] trustAllCerts = new javax.net.ssl.TrustManager[]{
                new javax.net.ssl.X509TrustManager() {
                    public java.security.cert.X509Certificate[] getAcceptedIssuers() { return null; }
                    public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
                    public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
                }
            };
            javax.net.ssl.SSLContext sc = javax.net.ssl.SSLContext.getInstance("SSL");
            sc.init(null, trustAllCerts, new java.security.SecureRandom());
            javax.net.ssl.HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
            javax.net.ssl.HttpsURLConnection.setDefaultHostnameVerifier((hostname, session) -> true);
        } catch (Exception e) {
        }
    }

    public static void main(String args[]) throws IOException {
        disableSSLCertificateChecking();


        Index5 index = new Index5();
        Crawler crawler = new Crawler();

        System.out.println("=== Step 1: Web Crawling ===");
        System.out.println("Seed URL: https://en.wikipedia.org/wiki/List_of_pharaohs");
        System.out.println("Crawling in progress... please wait...\n");
        crawler.crawl("https://en.wikipedia.org/wiki/List_of_pharaohs");

        List<String> crawledUrls = crawler.getVisitedUrls();
        System.out.println("\nCrawled " + crawledUrls.size() + " pages.");


        ArrayList<String> fileList = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            File f = new File("data/corpus/doc" + i + ".txt");
            if (f.exists()) fileList.add(f.getPath());
        }
        int N = fileList.size();

        if (N == 0) {
            System.out.println("No crawled documents found. Exiting.");
            return;
        }

        String[] files = fileList.toArray(new String[0]);


        System.out.println("\n=== Step 2: Building Inverted Index + TF ===");
        index.buildIndex(files);
        index.setN(N);
        System.out.println("Index built. Total unique terms: " + index.index.size());

        System.out.println("\n=== Step 3: Computing IDF ===");
        index.computeIDF(N);
        System.out.println("IDF computed for all terms.");


        System.out.println("\n=== Step 4: Building TF-IDF Document Vectors ===");
        index.buildDocVectors();
        System.out.println("Document vectors built for " + index.doc_vectors.size() + " documents.");

        // Map document IDs to their crawled URLs
        for (int i = 0; i < N; i++) {
            if (index.sources.get(i) != null) {
                if (i < crawledUrls.size()) index.sources.get(i).URL = crawledUrls.get(i);
                else                        index.sources.get(i).URL = files[i];
            }
        }


        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("\n=== TF-IDF Cosine Similarity Search ===");
        System.out.println("Type a query and press Enter. Press Enter on an empty line to quit.\n");

        while (true) {
            System.out.print("Enter your query: ");
            String query = in.readLine();
            if (query == null || query.trim().isEmpty()) break;


            Map<String, Double> queryVector = new HashMap<>();
            String[] queryTerms = query.toLowerCase().split("\\W+");
            Map<String, Integer> queryTf = new HashMap<>();

            for (String raw : queryTerms) {
                if (raw == null || raw.isEmpty()) continue;
                String term = index.stemWord(raw);
                if (!index.index.containsKey(term)) continue;
                queryTf.put(term, queryTf.getOrDefault(term, 0) + 1);
            }

            for (Map.Entry<String, Integer> e : queryTf.entrySet()) {
                String term    = e.getKey();
                double tf      = e.getValue();
                double idf     = index.index.get(term).idf;
                queryVector.put(term, tf * idf);  
            }

            if (queryVector.isEmpty()) {
                System.out.println("None of the query terms were found in the index.\n");
                continue;
            }

            Map<Integer, Double> scores = new HashMap<>();

            for (int i = 0; i < N; i++) {
                Map<String, Double> docVec = index.doc_vectors.getOrDefault(i, new HashMap<>());

                
                double score = index.getCosineSimilarity(queryVector, docVec);

              
                int docLength = (index.sources.get(i) != null) ? index.sources.get(i).length : 1;
                if (docLength > 0) {
                    score = score / docLength;
                }

                scores.put(i, score);
            }


            List<Map.Entry<Integer, Double>> ranked = new ArrayList<>(scores.entrySet());
            ranked.sort((a, b) -> b.getValue().compareTo(a.getValue()));

            System.out.println("\n--- Top " + Math.min(10, N) + " Results ---");
            System.out.printf("%-6s %-12s %s%n", "Rank", "Score", "URL");
            System.out.println("-".repeat(80));

            for (int i = 0; i < Math.min(10, ranked.size()); i++) {
                int    docId = ranked.get(i).getKey();
                double score = ranked.get(i).getValue();
                String url   = (index.sources.get(docId) != null)
                               ? index.sources.get(docId).URL
                               : files[docId];
                System.out.printf("%-6d %-12.6f %s%n", (i + 1), score, url);
            }
            System.out.println();
        }

        System.out.println("Goodbye!");
    }
}
