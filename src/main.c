#include <stdio.h>
#include "Question1.h"
#include "Question2.h"

int main() {
	int menu = 0;
	
	while (menu != 7) {
		printf("1. Brute Force Algorithm for Inversions\
		\n2. Divide and Conquer Algorithm for Inversions\
		\n3. Compare Execution Time for Inversions\
		\n4. Brute Force Algorithm for Convex Hull\
		\n5. Divide and Conquer Algorithm for Convex Hull\
		\n6. Compare Execution Time for Convex Hull\
		\n7. Exit\n");
		
		scanf("%d", &menu);
		
		if (menu == 1) {
			partQ1A();
		}
		else if (menu == 2) {
			partQ1B();
		}
		else if (menu == 3) {
			partQ1C();
		}
		else if (menu == 4) {
			partQ2A();
		}
		else if (menu == 5) {
			partQ2B();
		}
		else if (menu == 6) {
			partQ2C();
		}
		else if (menu == 7) {
			printf("Goodbye!\n");
		}
		else {
			printf("Invalid choice\n");
		}
		
		if (menu != 7) {
			printf("Press enter to continue...\n");
			while (getchar() != '\n');
			getchar();
		}
	}
	return 0;
}
