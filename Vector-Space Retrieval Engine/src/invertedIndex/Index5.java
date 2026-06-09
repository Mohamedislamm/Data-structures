package invertedIndex;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.Writer;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Index5 {

    private static final String STORAGE_DIR = "data/storage";
    int N = 0;
    public Map<Integer, SourceRecord> sources;
    public HashMap<String, DictEntry> index;
    public Map<Integer, Map<String, Double>> doc_vectors = new HashMap<>();

    public Index5() {
        sources = new HashMap<>();
        index   = new HashMap<>();
    }

    public void setN(int n) {
        N = n;
    }


    public void computeIDF(int N) {
        for (String term : index.keySet()) {
            DictEntry entry = index.get(term);
            if (entry.doc_freq > 0) {
                entry.idf = Math.log((double) N / entry.doc_freq);
            }
        }
    }

  
    public void buildDocVectors() {
        for (String term : index.keySet()) {
            DictEntry entry = index.get(term);
            Posting p = entry.pList;
            while (p != null) {
                double weight = p.dtf * entry.idf;   // TF * IDF
                doc_vectors.putIfAbsent(p.docId, new HashMap<>());
                doc_vectors.get(p.docId).put(term, weight);
                p = p.next;
            }
        }
    }


    public double getCosineSimilarity(Map<String, Double> queryVec,
                                      Map<String, Double> docVec) {
        double dotProduct = 0.0;

        for (String term : queryVec.keySet()) {
            if (docVec.containsKey(term)) {
                dotProduct += queryVec.get(term) * docVec.get(term);
            }
        }

        return dotProduct;
    }

    // -------------------------------------------------------
    public void printPostingList(Posting p) {
        System.out.print("[");
        while (p != null) {
            System.out.print(p.docId + p.positions.toString());
            p = p.next;
            if (p != null) System.out.print(", ");
        }
        System.out.println("]");
    }

    public void printDictionary() {
        Iterator it = index.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry) it.next();
            DictEntry dd   = (DictEntry) pair.getValue();
            System.out.print("** [" + pair.getKey() + "," + dd.doc_freq + "] =--> ");
            printPostingList(dd.pList);
        }
        System.out.println("------------------------------------------------------");
        System.out.println("*** Number of terms = " + index.size());
    }


    public void buildIndex(String[] files) {
        int fid = 0;
        for (String fileName : files) {
            try (BufferedReader file = new BufferedReader(new FileReader(fileName))) {
                sources.put(fid, new SourceRecord(fid, fileName, fileName, "notext"));
                String ln;
                int flen      = 0;
                int posOffset = 0;
                while ((ln = file.readLine()) != null) {
                    int wordsOnLine = indexOneLine(ln, fid, posOffset);
                    flen      += wordsOnLine;
                    posOffset += wordsOnLine;
                }
                sources.get(fid).length = flen;  
            } catch (IOException e) {
                System.out.println("File " + fileName + " not found. Skip it");
            }
            fid++;
        }
    }

    public int indexOneLine(String ln, int fid, int positionOffset) {
        String[] words = ln.split("\\W+");
        int wordCount  = words.length;
        for (int i = 0; i < words.length; i++) {
            String word = words[i].toLowerCase();
            if (stopWord(word)) continue;
            word = stemWord(word);
            int globalPos = positionOffset + i;
            if (!index.containsKey(word)) {
                index.put(word, new DictEntry());
            }
            DictEntry entry = index.get(word);
            if (!entry.postingListContains(fid)) {
                entry.doc_freq += 1;
                Posting newPosting = new Posting(fid);
                newPosting.positions.add(globalPos);
                if (entry.pList == null) {
                    entry.pList = newPosting;
                    entry.last  = newPosting;
                } else {
                    entry.last.next = newPosting;
                    entry.last      = entry.last.next;
                }
            } else {
                entry.last.dtf += 1;
                entry.last.positions.add(globalPos);
            }
            entry.term_freq += 1;
        }
        return wordCount;
    }


    boolean stopWord(String word) {
        switch (word) {
            // articles & prepositions
            case "the": case "a": case "an": case "of": case "in":
            case "to": case "for": case "from": case "at": case "by":
            case "on": case "with": case "as": case "into": case "about":
            case "through": case "during": case "before": case "after":
            case "above": case "below": case "between": case "out":
            case "off": case "over": case "under": case "again":
            case "up": case "down": case "within": case "without":
            // conjunctions & pronouns
            case "and": case "or": case "but": case "nor": case "so":
            case "yet": case "both": case "either": case "neither":
            case "that": case "which": case "who": case "whom": case "whose":
            case "this": case "these": case "those": case "such":
            case "he": case "she": case "it": case "they": case "we":
            case "his": case "her": case "its": case "their": case "our":
            case "him": case "them": case "us": case "my": case "your":
            // verbs
            case "be": case "is": case "are": case "was": case "were":
            case "been": case "being": case "have": case "has": case "had":
            case "do": case "does": case "did": case "will": case "would":
            case "shall": case "should": case "may": case "might":
            case "must": case "can": case "could": case "not":
            // common adverbs / other
            case "also": case "than": case "then": case "when":
            case "where": case "there": case "here": case "how":
            case "all": case "any": case "some": case "one": case "two":
            case "more": case "other": case "new": case "first":
            case "however": case "although": case "though":
                return true;
            default:
                return word.length() < 2;
        }
    }

    String stemWord(String word) {
        Stemmer s = new Stemmer();
        s.addString(word);
        s.stem();
        return s.toString();
    }

    // -------------------------------------------------------
    Posting intersect(Posting pL1, Posting pL2) {
        Posting answer = null;
        Posting last   = null;
        Posting p1 = pL1;
        Posting p2 = pL2;
        while (p1 != null && p2 != null) {
            if (p1.docId == p2.docId) {
                if (answer == null) {
                    answer = new Posting(p1.docId);
                    last   = answer;
                } else {
                    last.next = new Posting(p1.docId);
                    last      = last.next;
                }
                p1 = p1.next;
                p2 = p2.next;
            } else if (p1.docId < p2.docId) {
                p1 = p1.next;
            } else {
                p2 = p2.next;
            }
        }
        return answer;
    }

    Posting positionalIntersect(Posting pL1, Posting pL2, int gap) {
        Posting answer = null;
        Posting last   = null;
        Posting p1 = pL1;
        Posting p2 = pL2;
        while (p1 != null && p2 != null) {
            if (p1.docId == p2.docId) {
                ArrayList<Integer> matchPositions = new ArrayList<>();
                for (int pos1 : p1.positions) {
                    for (int pos2 : p2.positions) {
                        if (pos2 - pos1 == gap) {
                            matchPositions.add(pos2);
                        }
                    }
                }
                if (!matchPositions.isEmpty()) {
                    Posting newPost = new Posting(p1.docId, matchPositions);
                    if (answer == null) {
                        answer = newPost;
                        last   = answer;
                    } else {
                        last.next = newPost;
                        last      = last.next;
                    }
                }
                p1 = p1.next;
                p2 = p2.next;
            } else if (p1.docId < p2.docId) {
                p1 = p1.next;
            } else {
                p2 = p2.next;
            }
        }
        return answer;
    }

    public String find_24_01(String phrase) {
        String result = "";
        String[] words = phrase.split("\\W+");
        String firstStem = stemWord(words[0].toLowerCase());
        if (!index.containsKey(firstStem)) return "";
        Posting posting = index.get(firstStem).pList;
        for (int i = 1; i < words.length; i++) {
            String stem = stemWord(words[i].toLowerCase());
            if (!index.containsKey(stem)) return "";
            posting = intersect(posting, index.get(stem).pList);
            if (posting == null) return "";
        }
        while (posting != null) {
            result += "\t" + posting.docId
                    + " - " + sources.get(posting.docId).title
                    + " - " + sources.get(posting.docId).length + "\n";
            posting = posting.next;
        }
        return result;
    }

    public String phraseSearch(String phrase) {
        String result = "";
        String[] words = phrase.split("\\W+");
        ArrayList<String> stems = new ArrayList<>();
        for (String word : words) {
            stems.add(stemWord(word.toLowerCase()));
        }
        if (!index.containsKey(stems.get(0))) return "";
        Posting posting = index.get(stems.get(0)).pList;
        for (int i = 1; i < stems.size(); i++) {
            if (!index.containsKey(stems.get(i))) return "";
            posting = positionalIntersect(posting, index.get(stems.get(i)).pList, 1);
            if (posting == null) return "";
        }
        while (posting != null) {
            result += "\t" + posting.docId
                    + " - " + sources.get(posting.docId).title + "\n";
            posting = posting.next;
        }
        return result;
    }

    String[] sort(String[] words) {
        boolean sorted = false;
        String sTmp;
        while (!sorted) {
            sorted = true;
            for (int i = 0; i < words.length - 1; i++) {
                if (words[i].compareTo(words[i + 1]) > 0) {
                    sTmp         = words[i];
                    words[i]     = words[i + 1];
                    words[i + 1] = sTmp;
                    sorted       = false;
                }
            }
        }
        return words;
    }

    public void store(String storageName) {
        try {
            new java.io.File(STORAGE_DIR).mkdirs();
            Writer wr = new FileWriter(STORAGE_DIR + "/" + storageName);
            for (Map.Entry<Integer, SourceRecord> entry : sources.entrySet()) {
                wr.write(entry.getKey() + ",");
                wr.write(entry.getValue().URL + ",");
                wr.write(entry.getValue().title.replace(',', '~') + ",");
                wr.write(entry.getValue().length + ",");
                wr.write(String.format("%4.4f", entry.getValue().norm) + ",");
                wr.write(entry.getValue().text.replace(',', '~') + "\n");
            }
            wr.write("section2\n");
            Iterator it = index.entrySet().iterator();
            while (it.hasNext()) {
                Map.Entry pair = (Map.Entry) it.next();
                DictEntry dd   = (DictEntry) pair.getValue();
                wr.write(pair.getKey() + "," + dd.doc_freq + "," + dd.term_freq + ";");
                Posting p = dd.pList;
                while (p != null) {
                    wr.write(p.docId + "," + p.dtf + ",");
                    for (int k = 0; k < p.positions.size(); k++) {
                        wr.write(p.positions.get(k).toString());
                        if (k < p.positions.size() - 1) wr.write("|");
                    }
                    wr.write(":");
                    p = p.next;
                }
                wr.write("\n");
            }
            wr.write("end\n");
            wr.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public boolean storageFileExists(String storageName) {
        java.io.File f = new java.io.File(STORAGE_DIR + "/" + storageName);
        return f.exists() && !f.isDirectory();
    }

    public void createStore(String storageName) {
        try {
            new java.io.File(STORAGE_DIR).mkdirs();
            Writer wr = new FileWriter(STORAGE_DIR + "/" + storageName);
            wr.write("end\n");
            wr.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public HashMap<String, DictEntry> load(String storageName) {
        try {
            sources = new HashMap<>();
            index   = new HashMap<>();
            BufferedReader file = new BufferedReader(new FileReader(STORAGE_DIR + "/" + storageName));
            String ln;
            while ((ln = file.readLine()) != null) {
                if (ln.equalsIgnoreCase("section2")) break;
                String[] ss = ln.split(",");
                int fid = Integer.parseInt(ss[0]);
                try {
                    SourceRecord sr = new SourceRecord(
                            fid,
                            ss[1],
                            ss[2].replace('~', ','),
                            Integer.parseInt(ss[3]),
                            Double.parseDouble(ss[4]),
                            ss[5].replace('~', ','));
                    sources.put(fid, sr);
                } catch (Exception e) {
                    System.out.println(fid + "  ERROR  " + e.getMessage());
                }
            }
            while ((ln = file.readLine()) != null) {
                if (ln.equalsIgnoreCase("end")) break;
                String[] ss1  = ln.split(";");
                String[] meta = ss1[0].split(",");
                String[] postingTokens = ss1[1].split(":");
                index.put(meta[0], new DictEntry(
                        Integer.parseInt(meta[1]),
                        Integer.parseInt(meta[2])));
                for (String token : postingTokens) {
                    if (token.isEmpty()) continue;
                    String[] parts = token.split(",");
                    int docId = Integer.parseInt(parts[0]);
                    int dtf   = Integer.parseInt(parts[1]);
                    ArrayList<Integer> posList = new ArrayList<>();
                    if (parts.length > 2 && !parts[2].isEmpty()) {
                        for (String posStr : parts[2].split("\\|")) {
                            posList.add(Integer.parseInt(posStr));
                        }
                    }
                    Posting p = new Posting(docId, posList);
                    p.dtf = dtf;
                    if (index.get(meta[0]).pList == null) {
                        index.get(meta[0]).pList = p;
                        index.get(meta[0]).last  = p;
                    } else {
                        index.get(meta[0]).last.next = p;
                        index.get(meta[0]).last      = p;
                    }
                }
            }
            file.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return index;
    }
}
