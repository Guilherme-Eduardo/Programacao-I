#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "set.h"

// Creates an empty set capable of holding "size" values (from 0 to size -1)
// Return: pointer to the new set or NULL if failure
struct set_t *set_create (int max) {
	struct set_t *s;
	s = malloc (sizeof (struct set_t));
	if (!s) {
		printf ("Erro ao alocar set_t *s\n");
		return NULL;
	}
	s->flag = malloc (max * sizeof (bool));
	if (!s->flag) {
		printf ("Erro ao alocar s->flag\n");
		return NULL;
	}
	bzero (s->flag, max);
	s->num = 0;
	s->size = max;
	return s;
}

// Destroys the set, freeing its memory
// Return: NULL
struct set_t *set_destroy (struct set_t *s) {
	if (!s)
		return NULL;
	if (!s->flag)
		return NULL;
	free (s->flag);
	free (s);
	return NULL;
}

// Add an item to the set.
// Return: 1 if success or 0 if failure
int set_add (struct set_t *s, int item) {
	if (!s)
		return 0;
	if (!s->flag)
		return 0;
	if (item >= s->size)
		return 0;
	if (s->flag[item] == false) {
		s->flag[item] = true;
		s->num++;
	}
	return 1;
}

// Removes an item from the set.
// Return: 1 if success or 0 if failure
int set_del (struct set_t *s, int item) {
	if (!s)
		return 0;
	if (!s->flag)
		return 0;
	if (item >= s->size)
		return 0;
	if (s->flag[item] == true) {
		s->flag[item] = false;
		s->num--;
	}
	return 1;
}

// Verifies wether the item belongs to (is in) the set.
// Return: 1 if success or 0 if failure
int set_in (struct set_t *s, int item) {
	if (!s)
		return 0;
	if (!s->flag)
		return 0;
	return s->flag[item];	
}

// Verifies wether the set is empty
// Return: 1 if success or 0 if failure
int set_empty (struct set_t *s) {
	if (!s)
		return 0;
	if (!s->flag)
		return 0;
	if (s->num == 0) {
		printf ("Vetor vazio\n");
		return 1;
	}
	return 0;	
}


// Informs the set's cardinality (number of items or |S|)
// Return: n >=0 if success or -1 if failure
int set_card (struct set_t *s) {
	if (!s)
		return 0;
	if (!s->flag)
		return 0;
	if (s->num == 0)
		return 0;
	return s->num;
}

// Verifies wether s1 contains s2
// Return: 1 if success or 0 if failure
int set_contains (struct set_t *s1, struct set_t *s2) {
	if (!s1 || !s2)
		return 0;
	if (!s1->flag || !s2->flag)
		return 0;
	int i, maior;
	if (s1->size > s2->size)
		maior = s1->size;
	else
		maior = s2->size;
	for (i = 0; i < maior; i++) {
		if (s1->flag[i] == true && s2->flag[i] == false)
			return 0;
	}
	return 1;
}

// Verifies wether s1 == s2
// Return: 1 if success or 0 if failure
int set_equal (struct set_t *s1, struct set_t *s2) {
	if (!s1 || !s2)
		return 0;
	if (!s1->flag || !s2->flag)
		return 0;
	int i, maior;
	if (s1->size > s2->size)
		maior = s1->size;
	else
		maior = s2->size;
	for (i = 0; i < maior; i++) {
		if (s1->flag[i] != s2->flag[i])
			return 0;
	}
	return 1;
}

// Puts in s3 the union of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3) {
	if (!s1 || !s2)
		return 0;
	if (!s1->flag || !s2->flag)
		return 0;
	int i;
	for (i = 0; i < s3->size; i++) {
		if (s1->flag[i] == true || s2->flag[i] == true)
			s3->flag[i] = true;
	}

	return 1;
}

// Puts in s3 the intersection of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3) {
	if (!s1 || !s2)
		return 0;
	if (!s1->flag || !s2->flag)
		return 0;
	int i;
	for (i = 0; i < s3->size; i++) {
		if (s1->flag[i] == true && s2->flag[i] == true) {
			s3->flag[i] = true;
			s3->num++;
		}
	}
	return 1;
}

// Puts in s3 the difference s1 - s2; s3 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_diff (struct set_t *s1, struct set_t *s2, struct set_t *s3) {
	if (!s1 || !s2 || !s3)
		return 0;
	if (!s1->flag || !s2->flag || !s3->flag)
		return 0;
	int i;
	for (i = 0; i < s3->size; i++) {
		if (s1->flag[i] != s2->flag[i])
			s3->flag[i] = true;
	}
	return 1;
}

// Puts in s2 a copy of set s1; s2 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_copy (struct set_t *s1, struct set_t *s2) {
	if (!s1 || !s2)
		return 0;
	if (!s1->flag || !s2->flag)
		return 0;
	int i;
	for (i = 0; i < s2->size; i++) {
		s2->flag[i] = s1->flag[i];
	}
	return 1;
}

// Prints the content of a set using this template:
// [ %d %d %d ] (%d items)\n
// (Does not belong to the TAD definition, but is useful for testing)
void set_print (struct set_t *s) {
	if (!s)
		return;
	if (!s->flag)
		return;
	int i;
	printf ("[ ");
	for (i = 0; i < s->size; i++) {
		if (s->flag[i] == true) 
			printf (" %d ", i);
	}
	printf ("]\n");
}
