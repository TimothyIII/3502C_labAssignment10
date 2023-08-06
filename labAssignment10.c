#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* nextLetter[26];
    int word;
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    for (int i = 0; i < strlen(word); i++) {
        if (pTrie->nextLetter[(int)word[i] - (int)'a'] == NULL) {
            pTrie->nextLetter[(int)word[i] - (int)'a'] = createTrie();

        }
        pTrie = pTrie->nextLetter[(int)word[i] - (int)'a'];
    }
    pTrie->word++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *tmp = pTrie;

    for (int i = 0; i < strlen(word); i++) {
        if (tmp->nextLetter[(int)word[i] - (int)'a'] == NULL) return tmp->word;
        tmp = tmp->nextLetter[(int)word[i] - (int)'a'];
    }
    return tmp->word;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++) {
        if (pTrie->nextLetter[i] != NULL) {
            deallocateTrie(pTrie->nextLetter[i]);
            free(pTrie->nextLetter[i]);
        }
    }
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTrie = (struct Trie*)malloc(sizeof(struct Trie));
    myTrie->word = 0;
    for (int i = 0; i < 26; i++) {
        myTrie->nextLetter[i] = NULL;
    }
    return myTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* inFile = fopen(filename, "r");
    int numOfWords;
    fscanf(inFile, "%d", &numOfWords);

    for (int i = 0; i < numOfWords; i++) {
        pInWords[i] = (char*)malloc(30);
        fscanf(inFile, "%s ", pInWords[i]);
    }
    fclose(inFile);
    return numOfWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}