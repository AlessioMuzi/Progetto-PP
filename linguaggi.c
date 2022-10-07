/* programma per l'unione e la differenza dei linguaggi */
/* inclusione delle librerie */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

/* definizione delle costanti simboliche */
#define DOPPIONE       'D' /* contrassegno per le parole duplicate */
#define SEQUENZA_VUOTA 'V' /* contrassegno per le sequenze vuote */

/* dichiarazione delle funzioni */
int    inserisci_dim(char*);
char** allocazione_dinamica(int,   
		            int);  
char** inserisci_linguaggio(int,
		            int,
		            char*, 
		            char**);	   
char** ricerca_duplicati(int,
		         char**);       
char** unione_linguaggi(int,
		        int,
		        int,
		        int,
		        char**,     
		        char**,     
		        char**);        
char** differenza_linguaggi(int,
		            int,
			    char**,  
		            char**,    
			    char**); 
void   stampa_linguaggio(int,
		         char*,
	                 char**);       

/* definizione delle funzioni */
/* definizione della funzione main */
int main(void)
{
    char **linguaggio1,     /* input: primo linguaggio */
	 **linguaggio2,     /* input: secondo linguaggio */
	 **unione,          /* output: unione dei due linguaggi */
	 **differenza;      /* output: differenza dei due linguaggi */	
    int  num_parole1,       /* lavoro: numero di parole del primo linguaggio */
 	 num_parole2,       /* lavoro: numero di parole del secondo linguaggio */
	 lunghezza_max = 0; /* lavoro: lunghezza massima delle parole */

    /* inserimento del numero di parole dei due linguaggi input */
    num_parole1 = inserisci_dim("il numero di parole del primo linguaggio");
    num_parole2 = inserisci_dim("il numero di parole del secondo linguaggio");

    /* inserimento della lunghezza massima possibile delle parole */
    if ((num_parole1 == 0) && (num_parole2 == 0))
     printf("Entrambi i linguaggi sono vuoti, non è possibile eseguire nessun inserimento.\n");
    else
     lunghezza_max = inserisci_dim("la lunghezza massima possibile di una parola. Le sequenze vuote hanno lunghezza 0");

    /* allocazione dinamica dei linguaggi input e output */
    linguaggio1 = allocazione_dinamica(num_parole1,
		                       lunghezza_max);
    linguaggio2 = allocazione_dinamica(num_parole2,
		                       lunghezza_max);
    unione = allocazione_dinamica((num_parole1 + num_parole2),
			          lunghezza_max);
    differenza = allocazione_dinamica(num_parole1,
                                      lunghezza_max);

    /* promemoria dei simboli validi */
    printf("\nSimboli validi: {a, e, i, o, u}. Digitare '0' per inserire una sequenza vuota.\n");
    /* inserimento dei due linguaggi */
    if (num_parole1 != 0)
     linguaggio1 = inserisci_linguaggio(num_parole1,
			                lunghezza_max,
			                "primo",
			                linguaggio1);
    else
     printf("\nIl primo linguaggio è vuoto.\n");
    
    if (num_parole2 != 0)
     linguaggio2 = inserisci_linguaggio(num_parole2,
		                        lunghezza_max,
			                "secondo",
		                        linguaggio2);
    else
     printf("\nIl secondo linguaggio è vuoto.\n");
    
    /* unione dei due linguaggi */  
    unione = unione_linguaggi(num_parole1,
		              num_parole2,
		              0,
		              0,
		              linguaggio1,
		              linguaggio2,
		              unione);    
    /* differenza dei due linguaggi */
    differenza = differenza_linguaggi(num_parole1,
		                      num_parole2,
			              linguaggio1,
		                      linguaggio2,
			              differenza);

    /* stampa dell'unione dei due linguaggi */ 
    stampa_linguaggio((num_parole1 + num_parole2),
		      "Unione",
		      unione);  
    /* stampa della differenza dei due linguaggi */
    stampa_linguaggio(num_parole1,
		      "Differenza",
		      differenza);
    printf("\n");
    return(0);
}

/* definzione della funzione per inserire le dimensioni del linguaggio */
int inserisci_dim(char* messaggio) /* input: messaggio da stampare */
{
    int dim,    /* output: dimensione da inserire */
	esito;  /* lavoro: validazione degli input */

    printf("Inserisci %s.\n",
           messaggio);
    /* lettura e validazione delle dimensioni */
    do
    {
     esito = scanf("%d",
		   &dim);
     if (esito != 1 || dim < 0)
      printf("Valore non accettabile!\n");
     while (getchar() != '\n');
    }
    while (esito != 1 || dim < 0);

    return(dim);
}

/* definizione della funzione per l'allocazione dinamica della memoria */
char** allocazione_dinamica(int righe,    /* input: righe della matrice */
		            int colonne)  /* input: colonne della matrice */
{
    char** matrice; /* output: variabile per l'allocazione dinamica */
    int    i;       /* lavoro: indice per l'allocazione */
    
    /* allocazione dinamica */
    matrice = (char  **)malloc(righe * sizeof(char *));
     for (i = 0;
	  i < righe;
	  i++)
      matrice[i] = (char  *)malloc(colonne * sizeof(char));

    return(matrice);
}

/* definizione della funzione per l'inserimento dei linguaggi */
char** inserisci_linguaggio(int    parole,        /* input: numero di parole  */
	                    int    lunghezza_max, /* input: lunghezza massima delle parole */
			    char*  messaggio,     /* input: messaggio da stampare */
	                    char** matrice)       /* input: matrice allocata dinamicamente */
{
    int lunghezza_parola, /* input: lunghezza della prossima parola */
	i,                /* lavoro: indice per la lunghezza delle parole */
	j,                /* lavoro: indice per l'inserimento dei simboli */
	esito;            /* lavoro: validazione degli input */

    printf("\nInserimento del %s linguaggio.\n",
           messaggio);

    for (i = 0;
	 i < parole;
	 i++)
     {
      /* lettura e validazione della lunghezza della prossima parola */
      printf("Inserisci la lunghezza della prossima parola.\n");
      do
       {
        esito = scanf("%d",
                      &lunghezza_parola);
        if (esito != 1 || lunghezza_parola < 0 || lunghezza_parola > lunghezza_max)
         printf("Valore non accettabile!\n");
        while (getchar() != '\n');
       }
      while (esito != 1 || lunghezza_parola < 0 || lunghezza_parola > lunghezza_max);

     /* inserimento di un contrassegno per la SEQUENZA VUOTA */
     if (lunghezza_parola == 0)
      matrice[i][0] = SEQUENZA_VUOTA;
     else
      /* inserimento della parola, simbolo per simbolo */
      for (j = 0;
           j < lunghezza_parola;
 	   j++)
      {
       /* lettura e validazione dei simboli */
       printf("Inserisci il prossimo simbolo.\n");
       do
       {
        esito = scanf("%c",
	              &matrice[i][j]);
	if (esito != 1 || ((matrice[i][j] != 'a') && (matrice[i][j] != 'e') && 
	    (matrice[i][j] != 'i') && (matrice[i][j] != 'o') && (matrice[i][j] != 'u')))
	 printf("Simbolo non accettabile!\n");
	while (getchar() != '\n');
       }
       while (esito != 1 || ((matrice[i][j] != 'a') && (matrice[i][j] != 'e') && 
              (matrice[i][j] != 'i') && (matrice[i][j] != 'o') && (matrice[i][j] != 'u')));
      }
    } 
    /* ricerca di parole duplicate */
    matrice = ricerca_duplicati(parole,
		                matrice);

    return(matrice);
}

/* definizione della funzione per la ricerca di parole duplicate */
char** ricerca_duplicati(int    parole,    /* input: numero di parole del linguaggio */
	                 char** matrice)   /* input: linguaggio da cui rimuovere le parole duplicate */
{
    int i,         /* lavoro: indice per le righe */
	j,         /* lavoro: indice per il confronto */
	duplicato; /* lavoro: variabile per la ricerca di parole duplicate */

    /* confronto tra righe in ricerca delle parole duplicate */
    for (i = 0;
         i < parole;
	 i++)
     {
      /* è sufficiente confrontare ogni i-esima parola con le parole a partire dalla posizione i + 1 */
      for (j = (i + 1);
	   j < parole;
	   j++)
       {
        /* se due parole sono uguali, sostituiamo la seconda parola con DOPPIONE */
        duplicato = (strcmp(matrice[i], matrice[j]));
        if (duplicato == 0)
         matrice[j][0] = DOPPIONE;
      }
     }

    return(matrice);
}

/* definizione della funzione ricorsiva per l'unione dei due linguaggi */
char** unione_linguaggi(int    num_parole1,  /* input: numero parole del primo linguaggio */
		        int    num_parole2,  /* input: numero parole del secondo linguaggio */
		        int    i,            /* input: indice linguaggio1 e linguaggio unione */
		        int    j,            /* input: indice linguaggio2 */
		        char** linguaggio1,  /* input: primo linguaggio */
		        char** linguaggio2,  /* input: secondo linguaggio */
		        char** unione)       /* input: matrice risultato allocata dinamicamente */
{
    /* prima fase dell'unione: vengono caricate tutte le parole del primo linguaggio */
    if (num_parole1 != 0)
    {
     strcpy(unione[i], linguaggio1[i]);
     unione_linguaggi((num_parole1 - 1),
		      num_parole2,
		      (i + 1),
		      j,
                      linguaggio1,
	              linguaggio2,
		      unione);
    }
     /* seconda fase dell'unione: viene eseguita l'unione dei due linguaggi */
     /* se il secondo insieme non ha più elementi, l'unione termina */
     else if (num_parole2 != 0)
     {
      strcpy(unione[i], linguaggio2[j]);    
      unione_linguaggi(num_parole1,
		       (num_parole2 - 1),
		       (i + 1),
		       (j + 1),
		       linguaggio1,
	               linguaggio2,
		       unione);
    }
    /* ricerca di parole duplicate nel linguaggio unione */
    unione = ricerca_duplicati((num_parole1 + num_parole2),
		               unione);

    return(unione); 
}

/* definizione della funzione per la differenza dei due linguaggi */
char** differenza_linguaggi(int    num_parole1, /* input: numero parole del primo linguaggio */
			    int    num_parole2, /* input: numero parole del secondo linguaggio */
		            char** linguaggio1, /* input: primo linguaggio */
		            char** linguaggio2, /* input: secondo linguaggio */
			    char** differenza)  /* input: matrice risultato allocata dinamicamente */
{
    int i,    /* lavoro: indice linguaggio1 */
	j,    /* lavoro: indice linguaggio2 */
	k,    /* lavoro: indice linguaggio differenza */
	diff; /* lavoro: variabile per la differenza */

    /* differenza dei linguaggi */
    for (i = 0, k = 0;
         i < num_parole1;
	 i++)
     {
      for (j = 0, diff = 1;
           j < num_parole2;
	   j++)
       /* confronto tra la i-esima parola del primo linguaggio e tutte le parole del secondo linguaggio */
       diff *= (strcmp(linguaggio1[i], linguaggio2[j]));
      if (diff != 0)
      {
       /* inserimento delle parole nel linguaggio differenza */	      
       strcpy(differenza[k], linguaggio1[i]);
       k++;
      }
     }

    return(differenza);
}

/* definizione della funzione per la stampa dei due linguaggi */
void stampa_linguaggio(int    parole,    /* input: numero di parole */
		       char*  messaggio, /* input: messaggio da stampare */
		       char** matrice)   /* output: matrice da stampare */
{
    int i,              /* lavoro: indice per la stampa */
	insieme_vuoto;  /* lavoro: stampa dell'insieme vuoto */

    printf("\n%s dei due linguaggi:\n\n",
	   messaggio); 

    /* stampa delle parole */
    for (i = 0, insieme_vuoto = 0;
	 i < parole;
	 i++)
      /* stampa della sequenza vuota */
      if (matrice[i][0] == SEQUENZA_VUOTA)
      {
       printf(" *sequenza vuota*\n");
       insieme_vuoto++;
      }   
      /* se il programma legge DOPPIONE, la parola non verrà stampata */
      else if ((matrice[i][0] != DOPPIONE) && (matrice[i][0] != '\0'))
      {
       insieme_vuoto++;
       printf(" %s\n",
	      matrice[i]);
      }
    /* se il programma non ha stampato nulla, allora il linguaggio è vuoto */
    if (insieme_vuoto == 0)
     printf(" Insieme vuoto\n");
}
