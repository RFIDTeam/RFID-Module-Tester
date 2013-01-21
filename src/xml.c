 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <libxml/tree.h>
 #include <libxml/parser.h>
 #include <string.h>  


typedef void (*fct_parcours_t)(xmlNodePtr);


char* type = NULL;
char* issuer = NULL;
char* surName = NULL;
char* givenName = NULL;
char* number = NULL;
char* nationality = NULL;
char* dateOfBirth = NULL;
char* sex = NULL;
char* dateOfExpiry = NULL;



void parcours_arbre(xmlNodePtr noeud, fct_parcours_t f) {
    xmlNodePtr n;
    
    for (n = noeud; n != NULL; n = n->next) {
        f(n);
        if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
            parcours_arbre(n->children, f);
        }
    }
}

void afficher_noeud(xmlNodePtr noeud) {
    if (noeud->type == XML_ELEMENT_NODE) {
        if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE && strcmp (noeud->parent->name, "mrz") == 0 ) {
	    const xmlChar *nodename = noeud->name;
            xmlChar *content = xmlNodeGetContent(noeud);
            if (strcmp (noeud->name, "type") == 0){
              type = content;
              printf("%s : %s\n",nodename, type);
	    }
            if (strcmp (noeud->name, "issuer") == 0){
              issuer = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "surName") == 0){
              surName = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "givenName") == 0){
              givenName = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "number") == 0){
              number = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "nationality") == 0){
              nationality = content;
              printf("%s : %s\n",nodename, content);
	    } 
            if (strcmp (noeud->name, "dateOfBirth") == 0){
              dateOfBirth = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "sex") == 0){
              sex = content;
              printf("%s : %s\n",nodename, content);
	    }
            if (strcmp (noeud->name, "dateOfExpiry") == 0){
              dateOfExpiry = content;
              printf("%s : %s\n",nodename, content);
	    }
            xmlFree(content);
            
        }
    }
}

int main() {
    xmlDocPtr doc;
    xmlNodePtr racine;

    xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
    doc = xmlParseFile("/home/allanlorant/Desktop/RFID/mrtd.xml");
    if (doc == NULL) {
        fprintf(stderr, "Document XML invalide\n");
        return EXIT_FAILURE;
    }
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL) {
        fprintf(stderr, "Document XML vierge\n");
        xmlFreeDoc(doc);
        return EXIT_FAILURE;
    }

    printf("Données du passeport :\n");
    parcours_arbre(racine, afficher_noeud);

    xmlFreeDoc(doc);

    return EXIT_SUCCESS;
}
