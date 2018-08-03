#include <stdio.h>
#include <stdlib.h>
#define CREATE_VERTEX (vertex*)malloc(sizeof(vertex))
#define CREATE_NBH (nbh*)malloc(sizeof(nbh))

struct vertex{
	int vno, color;
	vertex *vnext;
	struct nbh *nnext;
	bool isAdminNo;
	int possibility[9];
	int possibleCount;

};


// int data1[75] = {1, 3, 8, 1, 5, 5, 1, 9, 2, 2, 2, 2, 2, 5, 9, 2, 8, 4, 2, 9, 1, 3, 3, 4, 3, 5, 3, 3, 9, 9, 4, 8, 1, 4, 9, 8, 6, 1, 5, 6, 2, 7, 6, 4, 4, 6, 7, 2, 7, 6, 7, 7, 9, 3, 8, 3, 7, 8, 5, 6, 8, 7, 4, 9, 2, 6, 9, 3, 1, 9, 4, 3, 9, 8, 9};
// int data1[84]  = {1, 2, 7, 1, 3, 1, 1, 5, 9, 1, 7, 8, 2, 4, 3, 2, 6, 6, 3, 1, 4, 3, 2, 9, 3, 7, 7, 3, 9, 5, 4, 2, 1, 4, 4, 9, 5, 1, 9, 5, 3, 2, 5, 7, 6, 5, 9, 3, 6, 6, 8, 6, 8, 2, 7, 1, 8, 7, 3, 5, 7, 8, 7, 7, 9, 6, 8, 4, 6, 8, 6, 7, 9, 3, 7, 9, 5, 4, 9, 7, 3, 9, 8, 5};
int data1[108] = {1, 4, 2, 1, 5, 6, 1, 7, 7, 1, 9, 1, 2, 1, 6, 2, 2, 8, 2, 5, 7, 2, 8, 9, 3, 1, 1, 3, 2, 9, 3, 6, 4, 3, 7, 5, 4, 1, 8, 4, 2, 2, 4, 4, 1, 4, 8, 4, 5, 3, 4, 5, 4, 6, 5, 6, 2, 5, 7, 9, 6, 2, 5, 6, 6, 3, 6, 8, 2, 6, 9, 8, 7, 3, 9, 7, 4, 3, 7, 8, 7, 7, 9, 4, 8, 2, 4, 8, 5, 5, 8, 8, 3, 8, 9, 6, 9, 1, 7, 9, 3, 3, 9, 5, 1, 9, 6, 8};


struct nbh{
	vertex *vadd;
	nbh *next;
};

vertex* createVertex(vertex **head, vertex **tail, int val){
	vertex *current = NULL;
	current = *tail;
	if(current == NULL){
		current = CREATE_VERTEX;
		*head = current;
		*tail = current;

	} else {
		current->vnext = CREATE_VERTEX;
		current = current->vnext;
		*tail = current;
	}
	current->vno = val;
	current->color = 0;
	current->isAdminNo = false;
	current->vnext = NULL;
	current->nnext = NULL;
	int i;
	for(i=0;i<9;i++){
		current->possibility[i] = 1;
	}
	current->possibleCount = 9;
	// printf("Created a vertex %d --> %u\n",current->vno, current);
	return current;
}

void createNbh(vertex **v1, vertex **v2){
	vertex *current = *v1;
	nbh *tempn;
	if(current->nnext == NULL){
		tempn = CREATE_NBH;
		tempn->vadd = *v2;
		tempn->next = NULL;
		current->nnext = tempn;
	} else{
		tempn = current->nnext;
		while(tempn->next != NULL)
			tempn = tempn->next;
		tempn->next = CREATE_NBH;
		tempn = tempn->next;
		tempn->vadd = *v2;
		tempn->next = NULL;

	}
	// printf("Created an Edge from %d (%u) --> %d (%u)\n", current->vno, current, (*v2)->vno, *v2);
}

void addVertex(vertex *head, int val1, int val2){
	vertex *temp1 = head;
	vertex *temp2 = head;

	while(temp1 != NULL && temp1->vno != val1)
		temp1 = temp1->vnext;

	while(temp2 != NULL && temp2->vno != val2)
		temp2 = temp2->vnext;

	if(temp1 && temp2)
		createNbh(&temp1, &temp2);
}

//prints colour of all vertices 
void displayColor(vertex *head){
	// printf("in displayColor\n");
	vertex *current = head;
	int count = 0;
	int j;
	for(j=1;j<=37;j++){
		printf("=");
	}
	printf("\n");

	while(current != NULL){
		count++;
		if(count % 9 == 1)
			printf("|");

		printf(" %d |", current->color);
		current = current->vnext;
		if(count % 9==0){
			printf("\n");
			for(j=1;j<=37;j++){
				printf("=");
			}
			printf("\n");
		}

	}
}

bool checkGameOver(vertex *head){
	// printf("in checkGameOver\n");
	vertex *current = head;
	int flag = 0;
	while(current != NULL){
		if(current->color == 0){
			flag = 1;
			return false;
		}
		current = current->vnext;
	}

	if(flag == 0)
		return true;
}

vertex* findVertex(vertex *head, int x, int y){
	// printf("in findVertex\n");
	vertex *current = head;
	int n = (x-1)*9 + y;
	while(current != NULL){
		if(current->vno == n){
			break;
		}
		current = current->vnext;
	}
	return current;
}

bool neighbourColorSame(vertex *head, vertex *v, int c){
	// printf("in neighbourColorSame\n");
	vertex *current = head ;
	nbh *ncurrent = v->nnext;
	int flag = 0;

	while(ncurrent != NULL){
		if(ncurrent->vadd->color == c){
			flag = 1;
		}
		ncurrent = ncurrent->next;
	}

	if(flag == 0){
		return false;
	}
	return true;
}


bool addColor(vertex **head, int x, int y, int c){
	// printf("In add color\n");
	vertex *v;
	v = findVertex(*head, x, y);
	if(v != NULL && !v->isAdminNo){
		if( !neighbourColorSame(*head,v,c)){
			v->color = c;
			return true;
		} else {
			printf("Sorry that is a wrong move!\n!!!!TRY AGAIN!!!!\n");
		}
	}
	if(v->isAdminNo){
		printf("Can not modify this number\n");
	}
	return false;
}

void findPossibility(vertex **head){
	// printf("in findVertex\n");
	vertex *current = *head, *v=NULL;
	nbh *ntemp;
	int x,y,i,temp;
	for(x=1;x<=9;x++){
		for(y=1;y<=9;y++){
			v = findVertex(*head, x, y);
			if(v != NULL && v->isAdminNo==false){
				printf("%d\t", v->vno);

				ntemp = v->nnext;

				while(ntemp != NULL ){
					temp = ntemp->vadd->color;
					if(temp != -1){
						v->possibility[temp-1] = -1;
					}
					ntemp = ntemp->next;
				}

				v->possibleCount = 0;
				for(i=0;i<9;i++){
					if(v->possibility[i] == 1)
						v->possibleCount += 1;
					printf("%d\t", v->possibility[i]);
				}
				printf("%d\n",v->possibleCount);
			}
		}
	}
}



bool singleRemaining(vertex **head){
	vertex *current = *head;
	int flag = 0;

	while(current != NULL){
		if( current->possibleCount == 1 && current->isAdminNo == false){
			return true;
		}
		current = current->vnext;
	}
	if(flag == 0)
		return false;

}

bool solveSudokuAgain(vertex **head){
	vertex *current = *head;
	int i;

	while(current != NULL){
		if(!current->isAdminNo){
			break;
		}
		current = current->vnext;
	}

	if(current){
		for(i=1;i<=9;i++){
			if(current->possibility[i-1] == 1){
				if(!neighbourColorSame(*head, current, i)){
					current->color = i;
					current->isAdminNo = true;



					if(solveSudokuAgain(head))
						return true;

					current->isAdminNo = false;
					current->color = 0;
				}
			}
		}
	} else {
		return true;
	}
	return false;
}

bool solveSudoku(vertex **head){
	vertex *current = *head,*v=NULL;
	nbh *ntemp;
	int x=1,y=1,c=1,count,newColor,i,temp;
	findPossibility(head);
	while(true){
		if(x!=9)
			x = x%9;
		for(y=1;y<=9;y++){

			if(!singleRemaining(head)){
				printf("in second solving\n");
				solveSudokuAgain(head);
				return true;
			}
			
			v = findVertex(*head, x, y);
			if(v->isAdminNo == false){
				count = 0;
				for(i=0;i<=8;i++){
					if(v->possibility[i] == 1){
						count++;
						newColor = i+1;
						
					}
				}

				printf("Vno. --> %d\tCount --> %d\n",v->vno,count);

				if( v->isAdminNo==false && count == 1 ){
					printf("adding new color %d\n",newColor);
					v->color = newColor;
					v->isAdminNo = true;
					findPossibility(head);
					displayColor(*head);
				}
			}		
		}
		x++;
	}	
}

void playSudoku(vertex **head){
	vertex *current = *head;
	int x,y,c,quit=2;
	while( !checkGameOver(current) && quit == 2){

		int ch;
		printf("1: Enter next move ||  2:quit || 3: get Solution");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("Enter co-ordinate and value\n");
			scanf("%d %d %d",&x, &y, &c);
			addColor(head, x, y, c);
			displayColor(*head);
		}else if(ch==2)
		{
			return;
		}
		else if(ch==3){
			current = *head;
			while(current != NULL){
				if(!current->isAdminNo){
					current->color = 0;
				}
				current = current->vnext;
			}
			// printf("New disp\n");
			// displayColor(*head);
			solveSudoku(head);
			printf("Solution...\n");
		}
		// printf("1. Quit\n2. Continue\n");
		//scanf("%d", &quit);
	}
}
vertex * gridformation()
{
	vertex *head=NULL, *tail=NULL;
	int i,j,k,n,m;

	for(i=1;i<=81;i++){
		createVertex(&head, &tail,i);
	}

	for(i=1;i<=9;i++){
		for(j=1;j<=9;j++){
			m = j+9*(i-1);
			for(k=1;k<=8;k++){
				n = j+9*(i-1)+k;
				if(n > 9*i){
					n = n-9;
				}
				addVertex(head, m, n);
			}
			for(k=1;k<=8;k++){
				n = j+9*(i-1)+9*k;
				if(n > 72+j)
					n = n-81;
				addVertex(head,m, n );
			}
			if(m %27 == 1 || m%27 == 4 || m%27 == 7){
				addVertex(head, m, m+10);
				addVertex(head, m, m+11);
				addVertex(head, m, m+19);
				addVertex(head, m, m+20);
			}else if(m %27 == 2 || m%27 == 5 || m%27 == 8){
				addVertex(head, m, m+8);
				addVertex(head, m, m+10);
				addVertex(head, m, m+17);
				addVertex(head, m, m+19);
			}else if(m %27 == 3 || m%27 == 6 || m%27 == 9){
				addVertex(head, m, m+7);
				addVertex(head, m, m+8);
				addVertex(head, m, m+16);
				addVertex(head, m, m+17);
			}else if(m %27 == 10 || m%27 == 13 || m%27 == 16){
				addVertex(head, m, m-8);
				addVertex(head, m, m-7);
				addVertex(head, m, m+10);
				addVertex(head, m, m+11);
			}else if(m %27 == 11 || m%27 == 14 || m%27 == 17){
				addVertex(head, m, m-10);
				addVertex(head, m, m-8);
				addVertex(head, m, m+8);
				addVertex(head, m, m+10);
			}else if(m %27 == 12 || m%27 == 15 || m%27 == 18){
				addVertex(head, m, m-11);
				addVertex(head, m, m-10);
				addVertex(head, m, m+7);
				addVertex(head, m, m+8);
			}else if(m %27 == 19 || m%27 == 22 || m%27 == 25){
				addVertex(head, m, m-17);
				addVertex(head, m, m-16);
				addVertex(head, m, m-8);
				addVertex(head, m, m-7);
			}else if(m %27 == 20 || m%27 == 23 || m%27 == 26){
				addVertex(head, m, m-19);
				addVertex(head, m, m-17);
				addVertex(head, m, m-10);
				addVertex(head, m, m-8);
			}else if(m %27 == 21 || m%27 == 24 || m%27 == 0){
				addVertex(head, m, m-20);
				addVertex(head, m, m-19);
				addVertex(head, m, m-11);
				addVertex(head, m, m-10);
			}
		}
	}
	return head;

}

void eneterValue(vertex *head)
{
	printf("\n");
	displayColor(head);
	int x,y,c,fixNo,count=1;
	vertex *v;

	printf("Enter the number of fix nodes ");
	scanf("%d", &fixNo);
	while(count<= fixNo){
		printf("Enter co-ordinate and value\n");
		scanf("%d %d %d",&x, &y, &c);
		v = findVertex(head, x, y);
		if(v != NULL && v->isAdminNo==false){
			if( !neighbourColorSame(head,v,c)){
				v->color = c;
				v->isAdminNo = true;
				count++;
			} else {
				printf("What are you doing admin\nEnter a correct value\n\n");
			}
		} else {
			printf("It is already assigned a value\n\n");
		}
		// displayColor(head);
	}
}


void allotExample(vertex **head){

	printf("in allot examp\n");
	vertex *current = *head;
	int n = sizeof(data1)/sizeof(data1[0]);
	int count = -1,i,val,x,y;
	for(i=0;i<n/3;i++){
		// if(i%3 == 0){
		printf("in allot\n");
			
			x = data1[++count];
			y = data1[++count];
			val = data1[++count];

			current = findVertex(*head, x, y);
			current->color = val;
			current->isAdminNo = true;

	}
}

int main(){

	
	vertex *head=gridformation();
	int choice;


	printf("...............................................SudokU........................................\n");
	printf("ENTER 1  TO  Play \n");
	printf("ENTER 2  TO Solve YOUR SudokU PROBLEM\n");
	printf("............................................................................................\n");
	scanf("%d", &choice);
	if(choice==1)
	{	
		// eneterValue(head);
		allotExample(&head);
		displayColor(head);
		playSudoku(&head);
		//playmain();
	}
	else{
		printf(".................................Solve your SudokU problem.................................\n");
		printf("INSTRUCTION:enter the total number of fixed vertices and then enter all the cordinates of the vertices along with their value one by one\n");
		//solvermain();
		eneterValue(head);
		solveSudoku(&head);
	}
	//displayColor(head);
	//printf("\n%d\n", checkGameOver(head));
	//findPossibility(&head);
	
	//
	if(checkGameOver(head))
	{
		displayColor(head);
	}
	else{
		printf("Failure!!!!");
	}
	
		//displayColor(head);
	return 0;
}

// 1 3 8 1 5 5 1 9 2 2 2 2 2 5 9 2 8 4 2 9 1 3 3 4 3 5 3 3 9 9 4 8 1 4 9 8 6 1 5 6 2 7 6 4 4 6 7 2 7 6 7 7 9 3 8 3 7 8 5 6 8 7 4 9 2 6 9 3 1 9 4 3 9 8 9

// 1 2 7 1 3 1 1 5 9 1 7 8 2 4 3 2 6 6 3 1 4 3 2 9 3 7 7 3 9 5 4 2 1 4 4 9 5 1 9 5 3 2 5 7 6 5 9 3 6 6 8 6 8 2 7 1 8 7 3 5 7 8 7 7 9 6 8 4 6 8 6 7 9 3 7 9 5 4 9 7 3 9 8 5

// 1 4 2 1 5 6 1 7 7 1 9 1 2 1 6 2 2 8 2 5 7 2 8 9 3 1 1 3 2 9 3 6 4 3 7 5 4 1 8 4 2 2 4 4 1 4 8 4 5 3 4 5 4 6 5 6 2 5 7 9 6 2 5 6 6 3 6 8 2 6 9 8 7 3 9 7 4 3 7 8 7 7 9 4 8 2 4 8 5 5 8 8 3 8 9 6 9 1 7 9 3 3 9 5 1 9 6 8

