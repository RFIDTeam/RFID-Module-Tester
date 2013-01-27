#include "xmlReader.h"

#define DEFAULT_FILE "main.c"


char* type = NULL;
char* issuer = NULL;
char* surName = NULL;
char* givenName = NULL;
char* number = NULL;
char* nationality = NULL;
char* dateOfBirth = NULL;
char* sex = NULL;
char* dateOfExpiry = NULL;


void parcours_arbre(xmlNodePtr noeud, fct_parcours_t f)
{
    xmlNodePtr n;

    for (n = noeud; n != NULL; n = n->next) {
        f(n);
        if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
            parcours_arbre(n->children, afficher_noeud);
        }
    }
}


void afficher_noeud(xmlNodePtr noeud)
{
    if (noeud->type == XML_ELEMENT_NODE) {
        if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE && strcmp (noeud->parent->name, "mrz") == 0 ) {
            const xmlChar *nodename = noeud->name;
            if (strcmp (noeud->name, "type") == 0){
                type = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "issuer") == 0){
                issuer = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "surName") == 0){
                surName = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "givenName") == 0){
                givenName = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "number") == 0){
                number = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "nationality") == 0){
                nationality = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "dateOfBirth") == 0){
                dateOfBirth = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "sex") == 0){
                sex = xmlNodeGetContent(noeud);
            }
            if (strcmp (noeud->name, "dateOfExpiry") == 0){
                dateOfExpiry = xmlNodeGetContent(noeud);
            }
        }
    }
}


char** xmlRead(char* xmlFilePath)
{
    xmlDocPtr doc;
    xmlNodePtr racine;
    int i=0;

    char **data=(char**)malloc(sizeof(char*)*10);
    for(i=0 ; i<10 ; i++){
        data[i]=(char*)malloc(50);
    }

    xmlKeepBlanksDefault(0); // Ignore formating text nodes
    doc = xmlParseFile(xmlFilePath);
    if (doc == NULL) {
        fprintf(stderr, "Invalid XML file\n");
    }
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL) {
        fprintf(stderr, "Empty XML file\n");
        xmlFreeDoc(doc);
    }

    parcours_arbre(racine, afficher_noeud);

    strcpy(data[0], type);
    strcpy(data[1], issuer);
    strcpy(data[2], surName);
    strcpy(data[3], givenName);
    strcpy(data[4], number);
    strcpy(data[5], nationality);
    strcpy(data[6], dateOfBirth);
    strcpy(data[7], sex);
    strcpy(data[8], dateOfExpiry);

    xmlFreeDoc(doc);
    return data;
}
