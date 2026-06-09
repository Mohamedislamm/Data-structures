/*
 * Positional Index version of Posting
 * Each posting stores the document ID and a list of positions
 * where the term appears within that document.
 */
package invertedIndex;

import java.util.ArrayList;

/**
 * Represents a single node in a posting list.
 * In the positional index, each node stores the document ID,
 * how many times the term appears (dtf), and the exact
 * word-positions within that document.
 *
 * @author ehab (extended for positional index)
 */
public class Posting {

    public Posting next = null;

    
    int docId;

    
    int dtf = 1;

    
    ArrayList<Integer> positions;

    // -------------------------------------------------------
    /**
     * Constructs a Posting for the given document ID and term frequency,
     * initialising an empty positions list.
     *
     * @param id The document ID.
     * @param t  The term frequency in this document.
     */
    Posting(int id, int t) {
        docId = id;
        dtf   = t;
        positions = new ArrayList<>();
    }

    // -------------------------------------------------------
    /**
     * Constructs a Posting for the given document ID with dtf = 1,
     * initialising an empty positions list.
     *
     * @param id The document ID.
     */
    Posting(int id) {
        docId = id;
        positions = new ArrayList<>();
    }

    // -------------------------------------------------------
    /**
     * Constructs a Posting with a pre-built positions list.
     * Used during positional intersection to carry surviving positions.
     *
     * @param id  The document ID.
     * @param pos The list of positions to store.
     */
    Posting(int id, ArrayList<Integer> pos) {
        docId     = id;
        dtf       = pos.size();
        positions = new ArrayList<>(pos);
    }
}
