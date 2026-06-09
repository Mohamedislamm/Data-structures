package invertedIndex;

public class DictEntry {

    public int doc_freq = 0;
    public int term_freq = 0;
    public double idf = 0;

    Posting pList = null;
    Posting last = null;

    boolean postingListContains(int i) {
        Posting p = pList;
        while (p != null) {
            if (p.docId == i) {
                return true;
            }
            p = p.next;
        }
        return false;
    }

    int getPosting(int i) {
        Posting p = pList;
        while (p != null) {
            if (p.docId >= i) {
                if (p.docId == i) {
                    return p.dtf;
                } else {
                    return 0;
                }
            }
            p = p.next;
        }
        return 0;
    }

    void addPosting(int i) {
        if (pList == null) {
            pList = new Posting(i);
            last = pList;
        } else {
            if(last.docId == i) {
                last.dtf++;
            } else {
                last.next = new Posting(i);
                last = last.next;
            }
        }
    }

    DictEntry() {
    }

    DictEntry(int df, int tf) {
        doc_freq = df; 
        term_freq = tf;
    }
}