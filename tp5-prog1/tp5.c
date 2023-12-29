// TAD conjunto de inteiros - arquivo de teste
// Carlos Maziero, Set 2023

#include <stdio.h>
#include "set.h"

int main () {
	
	struct set_t *sa, *sb, *se, *su, *si, *sd, *sc, *sh ;

	printf ("==== set_create\n") ;
	sa = set_create (100) ;
	sb = set_create (100) ;
	printf ("sa: ") ;
	set_print (sa) ;
	printf ("sb: ") ;
	set_print (sb) ;

	printf ("=== set_add\n") ;
	for (int i = 20; i > 0; i-=2)
		set_add (sa, i) ;
	printf ("sa: ") ;
	set_print (sa) ;

	for (int i = 1; i < 20; i+=2)
		set_add (sb, i) ;
	printf ("sb: ") ;
	set_print (sb) ;

	printf ("=== set_del\n") ;
	printf ("Deleting from sa: ") ;
	for (int i = 6; i < 16; i++)
	{ 
		printf ("%d ", i) ;
		set_del (sa, i) ;
	}
	printf ("\n") ;
	printf ("sa: ") ;
	set_print (sa) ;

	printf ("Deleting from sb: ") ;
	for (int i = 16; i >=6; i--)
	{ 
		printf ("%d ", i) ;
		set_del (sb, i) ;
	}
	printf ("\n") ;
	printf ("sb: ") ;
	set_print (sb) ;

	printf ("=== set_equal\n") ;
	se = set_create (100) ;
	for (int i = 20; i > 0; i-=2)
		set_add (se, i) ;
	for (int i = 6; i < 16; i++)
		set_del (se, i) ;
	printf ("sa: ") ;
	set_print (sa) ;
	printf ("sb: ") ;
	set_print (sb) ;
	printf ("se: ") ;
	set_print (se) ;
	if (set_equal (sa, sb))
		printf ("sa and sb are equal\n") ;
	else
		printf ("sa and sb are different\n") ;
	if (set_equal (sa, se))
		printf ("sa and se are equal\n") ;
	else
		printf ("sa and se are different\n") ;

	printf ("=== set_union\n") ;
	su = set_create (100) ;
	set_union (sa, sb, su) ;
	printf ("sa: ") ;
	set_print (sa) ;
	printf ("sb: ") ;
	set_print (sb) ;
	printf ("su: ") ;
	set_print (su) ;

	printf ("=== set_intersect\n") ;
	set_add (se, 7) ;
	set_add (se, 35) ;
	si = set_create (100) ;
	set_intersect (se, su, si) ;
	printf ("se: ") ;
	set_print (se) ;
	printf ("su: ") ;
	set_print (su) ;
	printf ("si: ") ;
	set_print (si) ;

	printf ("=== set_diff (se - su)\n") ;
	sd = set_create (100) ;
	set_diff (se, su, sd) ;
	printf ("se: ") ;
	set_print (se) ;
	printf ("su: ") ;
	set_print (su) ;
	printf ("sd: ") ;
	set_print (sd) ;

	printf ("=== set_contains\n") ;
	if (set_contains (su, sa))
		printf ("su contains sa\n") ;
	else
		printf ("su does not contain sa\n") ;
	if (set_contains (su, sb))
		printf ("su contains sb\n") ;
	else
		printf ("su does not contain sb\n") ;
	if (set_contains (su, sd))
		printf ("su contains sd\n") ;
	else
		printf ("su does not contain sd\n") ;

	printf ("=== set_copy\n") ;
	sc = set_create (100) ;
	set_copy (su, sc) ;
	printf ("su: ") ;
	set_print (su) ;
	printf ("sc: ") ;
	set_print (sc) ;

	printf ("=== huge set\n") ;
	sh = set_create (50000) ;
	for (int i = 0; i < 50000; i++)
		set_add (sh, i) ;
	printf ("sh has %d items\n", set_card (sh)) ;

	printf ("=== set_destroy\n") ;
	set_destroy (sa) ;
	set_destroy (sb) ;
	set_destroy (se) ;
	set_destroy (su) ;
	set_destroy (si) ;
	set_destroy (sd) ;
	set_destroy (sc) ;
	set_destroy (sh) ;
}

