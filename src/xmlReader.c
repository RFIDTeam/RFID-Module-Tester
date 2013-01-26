#include "xmlReader.h"

#define DEFAULT_FILE "main.c"


void parcours_arbre(xmlNodePtr noeud, fct_parcours_t f, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry)
{
    xmlNodePtr n;

    for (n = noeud; n != NULL; n = n->next) {
        f(n, type, issuer, surName, givenName, number, nationality, dateOfBirth, sex, dateOfExpiry);
        if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
            parcours_arbre(n->children, afficher_noeud, type, issuer, surName, givenName, number, nationality, dateOfBirth, sex, dateOfExpiry);

        }
    }
}


void afficher_noeud(xmlNodePtr noeud, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry)
{
    if (noeud->type == XML_ELEMENT_NODE) {
        if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE && strcmp (noeud->parent->name, "mrz") == 0 ) {
	    const xmlChar *nodename = noeud->name;
            xmlChar *content = xmlNodeGetContent(noeud);

            if (strcmp (noeud->name, "type") == 0){
              type = content;
	    }
            if (strcmp (noeud->name, "issuer") == 0){
              issuer = content;
	    }
            if (strcmp (noeud->name, "surName") == 0){
              surName = content;
	    }
            if (strcmp (noeud->name, "givenName") == 0){
              givenName = content;
	    }
            if (strcmp (noeud->name, "number") == 0){
              number = content;
	    }
            if (strcmp (noeud->name, "nationality") == 0){
              nationality = content;
	    }
            if (strcmp (noeud->name, "dateOfBirth") == 0){
              dateOfBirth = content;
	    }
            if (strcmp (noeud->name, "sex") == 0){
              sex = content;
	    }
            if (strcmp (noeud->name, "dateOfExpiry") == 0){
              dateOfExpiry = content;
	    }
            xmlFree(content);

        }
    }
}


xmlRead(char* xmlFilePath, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry)
{
    xmlDocPtr doc;
    xmlNodePtr racine;

    xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
    doc = xmlParseFile(xmlFilePath);
    if (doc == NULL) {
        fprintf(stderr, "Invalid XML file\n");
    }
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL) {
        fprintf(stderr, "Empty XML file\n");
        xmlFreeDoc(doc);
    }
    parcours_arbre(racine, afficher_noeud, type, issuer, surName, givenName, number, nationality, dateOfBirth, sex, dateOfExpiry);

    xmlFreeDoc(doc);
}
