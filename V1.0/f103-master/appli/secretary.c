/*
 * secretary.c
 *
 *  Created on: 28 mars 2019
 *      Author: Nirgal
 */
#include "secretary.h"
#include "macro_types.h"
#include "stm32f1_uart.h"
#include "stm32f1_rtc.h"

#define BUFFER_SIZE	128
static void find_command(char * buffer);
static void echo_command(char * buffer);
static bool_e str_begin_with(char * string, char * begin);


void maj2min(char *s) {
    // Parcourir chaque caractère de la chaîne jusqu'à rencontrer le caractère nul '\0'
    while (*s != '\0') {
        // Vérifier si le caractère actuel est une majuscule
        if (*s >= 'A' && *s <= 'Z') {
            // Convertir en minuscule en ajoutant la différence entre 'a' et 'A'
            *s = *s + ('a' - 'A');
        }
        // Passer au caractère suivant
        s++;
    }
}

void SECRETARY_process_main(void)
{
    static char buffer[BUFFER_SIZE];
    static uint8_t index = 0;
    char c;

    while (UART_data_ready(UART2_ID)) // Tant que des données sont disponibles sur l'UART2
    {
        c = UART_getc(UART2_ID); // Lire le prochain caractère
        buffer[index] = c; // Ranger c dans la case index du tableau buffer

        if (c == '\n') // Si c'est la fin de la commande (caractère de fin de ligne)
        {
            buffer[index] = '\0'; // Ecraser le '\n' par un '\0' pour terminer la chaîne
            find_command(buffer); // Traiter la commande
            index = 0; // Remettre l'index à 0 pour la prochaine commande
        }
        else if (index < BUFFER_SIZE - 1) // Vérifier l'espace disponible dans le buffer
        {
            index++; // Préparer l'index pour le prochain caractère
        }
    }
}

/**
* @brief 	Fonction privée qui analyse le contenu de la chaine string pour voir si elle commence par le contenu de la chaine begin
* @param	string : la chaine dans laquelle on recherche
* @param	begin : la chaine que l'on recherche
* @pre		begin doit être de taille inférieure à string
* @ret		TRUE si string commence par begin. FALSE sinon.
*/
static bool_e str_begin_with(char * string, char * begin)
{
	bool_e ret;
	uint16_t i;

	ret = TRUE;
	for(i = 0; begin[i]!='\0'; i++){
		if (string[i]== 0 || string[i] != begin[i]){
			ret = FALSE;
			break;
		}
	}
	return ret;
}




static void echo_command(char * buffer)
{
	puts(buffer);
}

static void find_command(char * buffer)
{
	maj2min(buffer);
	bool_e badstring;
	badstring = FALSE; //On fait l'hypothèse que la chaine est correcte.

	if(str_begin_with(buffer, "incline_x"))
	{

	}
	else if(str_begin_with(buffer, "incline_y")){

	}
	else if(str_begin_with(buffer, "geoloc")){

	}
	else if(str_begin_with(buffer, "acceleration")){

	}
	else if(str_begin_with(buffer, "help"))
	{
		printf("--- commands list with examples ---\n");
		printf("\"help\\n\" - show this commands list \n");
	}
	else
		badstring = TRUE;
	if(badstring)
		printf("Bad command -> press help to list commands\n");
}
