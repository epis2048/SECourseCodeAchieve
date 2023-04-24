/**
 * This class is the XML parser class. This class loads in an XML file. The data from the output can
 * be used in other classes.
 *
 * @author Rico de Feijter, Marcellino van Hecke
 * @version 1.0
 */
package cn.edu.whut.sept.zuul;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.HashMap;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

public class XMLParser extends DefaultHandler {

    /*
     * Fields
     */
    private String filename;
    private int parentID;
    private String currentElement;
    private String xmlSplit;

    private static HashMap<Integer, HashMap<String, String>> xmlData;

    /**
     * Constructor
     */
    public XMLParser() {
        xmlData = new HashMap<Integer, HashMap<String, String>>();
    }

    /*
     * Run the xml converter
     */
    public void runXMLConvert() throws Exception {
        // Create SAX 2 parser...
        XMLReader xr = XMLReaderFactory.createXMLReader();

        // Set the ContentHandler...
        xr.setContentHandler(new XMLParser());

        FileReader xmlFile = null;

        try {
            //Get file contents
            xmlFile = new FileReader(this.getFilename());
        } catch (FileNotFoundException e) {
            System.err.println("Bestand niet gevonden: " + this.getFilename()
                + ". Dit bestand is vereist voor een correcte werking van het spel.");
        } finally {
            // Parse the file...
            xr.parse(new InputSource(xmlFile));

            //Close XMl file
            xmlFile.close();
        }
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes attr)
        throws SAXException {

        if (!qName.equals(xmlSplit)) {
            currentElement = localName;

            // Also, let's print the attributes if
            // there are any...
            for (int i = 0; i < attr.getLength(); i++) {
                parentID = Integer.parseInt(attr.getValue(i).replaceAll("[^0-9]+", ""));

                xmlData.put(parentID, new HashMap<String, String>());
            }
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException {
        try {
            String fieldValue = new String(ch, start, length);

            if (fieldValue.trim().length() > 0) {
                xmlData.get(parentID).put(currentElement, fieldValue);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    /*
     * Give in a filename and split the name on .xml
     * @param String filename
     */
    public void setFilename(String filename) {
        this.filename = filename;

        String str = this.filename;
        String[] tokens = str.split("/");
        String lastOne = tokens[tokens.length - 1];

        String xmlSplit[] = lastOne.split(".xml");
        String xmlSplitOutput = xmlSplit[0];
        this.xmlSplit = xmlSplitOutput;
    }

    /*
     * Return the filename
     * @return String filename
     */
    public String getFilename() {
        return this.filename;
    }

    /*
     * Return the xmlData
     * @return Hashhmap xmlData
     */
    public HashMap getXMLData() {
        return xmlData;
    }

}