/*
This program uses a Monte Carlo approximation to compute the probabilities of 
a poker hand of 7 cards being either 3 or 4 of a kind, 1 or 2 pair, full house
or no pair at all. If a number of total studs for a category appears to not be
accurate that is because the results are calculated for very few times. In order
to get results true to the theoretical, it should run for a very large amount of times.
If the original number is too large for your system, use a smaller one.
~Ioannis SYmeonidis
*/
#include <stdio.h>     
#include <stdlib.h> 
#include <time.h>
#define N 1000000 //change this according to the times you wish to repeat the simulation

typedef enum suit{Red_Hearts,Red_Diamonds,Black_Clubs,Black_Spades} suit; //all types of suits as enums
typedef enum stud{no_pair,one_pair,two_pair,three_of_a_kind,full_house,four_of_a_kind}stud ;//all types of studs as enums

typedef struct card{ //struct card with suit and pips
	suit s;
	short int p;
}card;
typedef struct hand{ //struct hand that contains 7 cards
	card Card[7];
	stud Stud;
}hand;

card* Init_Deck(); //Initialises the deck and returns it.
card* Shuffle_deck(card* );//Shuffles a deck and returns it, deleting the old deck.
hand* deal_hands(card*, int*,int *, int *,int *,int *,int *,int *); //deals the cards to 7 hands and takes references of the stud counters 
int comp(const void*, const void *); // compare function used by qsort
stud evaluate_hand(hand,int*,int*,int *,int *,int *,int *,int *);//evaluates the stud of the hand and also takes references of the stud counters

int main(void)
{
	//initialise all counters
	int G=0;
	int FH=0;
	int FOAK=0;
	int TOAK=0;
	int TP=0;
	int OP = 0;
	int NP = 0;
	int k=0;
	//Repeat the experiment for N times.
	//This may take a few seconds according to your computing power
	//and according to the number of times you want to repeat it.
	//Larger numbers offer higher accuracy.
	for(k=0;k<N;k++)
	{
		card* Deck = Init_Deck();
		Deck = Shuffle_deck(Deck);
		hand * hands;
		hands = deal_hands(Deck,&G,&FH,&FOAK,&TOAK,&TP,&OP,&NP);
		free(hands); //free the used hands from memory
	}
	int denominator = (7*N)/100; 
	// to get the correct results, the times it has ran must be multiplied by 7 
	//since each deck gives 7 hands, and in order to get a precentage
	//it must be divided by 100.
	printf("\nThe calculated probabilities are:\n");
	printf("\nFULL HOUSE:       %d%%\n", FH/denominator);
	printf("\nFOUR OF A KIND:   %d%%\n", FOAK/denominator);
	printf("\nTHREE OF A KIND:  %d%%\n", TOAK/denominator);
	printf("\nTWO PAIR:         %d%%\n", TP/denominator);
	printf("\nONE PAIR:         %d%%\n", OP/denominator);
	printf("\nNO PAIR(OTHER):   %d%%\n", NP/denominator);
	printf("\nTOTAL:            %d%%\n", (FH+FOAK+TOAK+TP+OP+NP)/denominator);
}

card* Init_Deck()
{
	//Create a total of 52 unique cards
	//and then return the created deck
	card* Deck = malloc(sizeof(card)*52);
	int i=0;
	for(i=0;i<13;i++)
	{
		Deck[i].s = Red_Hearts;
		Deck[i].p = i+1;
	}
	for(i=0;i<13;i++)
	{
		Deck[i+13].s = Red_Diamonds;
		Deck[i+13].p = i+1;
	}
	for(i=0;i<13;i++)
	{
		Deck[i+26].s = Black_Clubs;
		Deck[i+26].p = i+1;
	}
	for(i=0;i<13;i++)
	{
		Deck[i+39].s = Black_Spades;
		Deck[i+39].p = i+1;
	}
	return Deck;
}
card* Shuffle_deck(card* Deck)
{
	int used_elements[52]; //this array keeps track of all shuffled cards from the initialised deck
	int i;
	for(i=0;i<52;i++)
		used_elements[i]=0;
	srand(time(0));
	card* new_Deck = malloc(sizeof(card)*52);
	
	int counter=0;
	//Pick a random number up to 52 to randomly select a card
	//then check if the card has already been shuffled.
	//If not, add it to the new deck and mark it as shuffled.
	while(counter<52)
	{
		int element = rand()%52;
		if(used_elements[element]!=1)
		{
			new_Deck[counter].p = Deck[element].p;
			new_Deck[counter].s = Deck[element].s;
			used_elements[element] =1;
			counter++;
		}
	}
	free(Deck); //delete the old deck from memory
	return new_Deck;
}
hand* deal_hands(card* Deck, int* G,int *FH, int *FOAK,int *TOAK,int *TP,int *OP,int *NP)
{
	//A hand consists of 7 cards.
	//Pick the first 7 cards you encounter in the deck
	//and place them in every hand.
	//Repeat for next 7 until you do it for 7 times totally.
	hand* hands =  malloc(sizeof(hand)*7);
	int i=0;
	int j=0;
	int counter = 0;
	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
			{
				hands[i].Card[j] = Deck[counter];
				counter++;
			}
		
		qsort(hands[i].Card,7,sizeof(card),comp); //use to sort the hand
		hands[i].Stud =  evaluate_hand(hands[i],G,FH,FOAK,TOAK,TP,OP,NP); //call for evaluation
	}
	free(Deck);//deletes the deck from memory
	//return all 7 hands.
	return hands;
}
int comp(const void* a, const void *b)
{
	//standard qsort implementation comparing the pips of the two cards
	const struct card * cardA = (card *)a;
	const struct card * cardB = (card *)b;
	
	if((cardA->p)<(cardB->p))
		return -1;
	else if((cardA->p)>(cardB->p))
		return 1;
	else
		return 0;
}
stud evaluate_hand(hand Hand, int* G,int *FH,int *FOAK, int *TOAK, int *TP, int *OP, int *NP)
{
	(*G)++;
	//check full house
	//In this case, if three cards have the same value
	//it searches for a pair of two cards with a different value in the hand.
	int i=0;
	int j=0;
	for(i=0;i<5;i++)
	{
		if(Hand.Card[i].p== Hand.Card[i+2].p )
			{
				int temp = Hand.Card[i].p;
				int k;
				for(k=0;k<6;k++)
					if(Hand.Card[k].p!=temp && Hand.Card[k].p== Hand.Card[k+1].p)
						{
							(*FH)++;
							return full_house;	
						}					
			}
	}
	//check four of a kind
	//Condition is of four consecuative cards have the same value.
	for(i=0;i<4;i++)
	{
		if(Hand.Card[i].p== Hand.Card[i+3].p )
			{
				(*FOAK)++;
				return four_of_a_kind;
			}		
	}
	//check three of a kind
	//Condition is if three consecuative cards have the same value.
	for(i=0;i<5;i++)
	{
		if(Hand.Card[i].p== Hand.Card[i+2].p )
			{
				(*TOAK)++;
				return three_of_a_kind;
			}	
	}
	//check for two pair
	//If there are two different pairs of same value.
	for(i=0;i<6;i++)
	{
		if(Hand.Card[i].p==Hand.Card[i+1].p)
			{
				int temp = Hand.Card[i].p;
				for(j=0;j<6;j++)
					if(Hand.Card[j].p==Hand.Card[j+1].p && Hand.Card[j].p!=temp)
					{
						(*TP)++;
						return two_pair;
					}
			}
	}
	//check for one pair
	//Simply search for two cards with the same value.
	for(i=0;i<6;i++)
	{
		if(Hand.Card[i].p==Hand.Card[i+1].p)
			{
				(*OP)++;
				return one_pair;
			}
	}
	
	//if none of the above conditions is met 
	//there is no pair (or other outside this exercise)
	(*NP)++;
	return no_pair;
}

