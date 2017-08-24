/*  Description: Code printing valid tables for the game of flow.
    Creator: Vaibhav Agarwal (vaiagarwal96@iitkgp.ac.in) */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _node
{
	struct _node *parent;
	int rank;
	int path_number;
	int endpoint;
};
typedef struct _node node;


/*    Name: initboard()
      Input: 2D-array of pointers, size of array row/column
      Output: --void--
      Description: Takes a table of pointers and initializes it. */
void initboard(node ***arr, int n)
{
	int i, j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			node *np;
			np = (node *)malloc(sizeof(node));
			np->rank = 0;
			np->parent = NULL;
			np->path_number = 0;
			np->endpoint = 0;
			arr[i][j] = np;
		}
	}
}
/***********************/


/*    Name: findset()
      Input: a node
      Output: the set pointer of the set the node belongs to
      Description: Takes a node and returns the set pointer. */
node *findset(node *n)
{
	if (n->parent != NULL)
		n = n->parent;
	return n;
}
/************************/



/*    Name: setunion()
      Input: nodes x and y
      Output: --void--
      Description: merges the two sets containing x and y.
*/
void setunion(node *x, node *y)
{
	x = findset(x);
	y = findset(y);
	if (x->rank > y->rank)
		y->parent = x;
	else{
		x->parent = y;
		if(x->rank == y->rank)
			y->rank++;
	}
}
/**************************/


/*    Name: neighbour()
      Input: size of array row/column, 2D-array of pointers
      Output: returns the incripted values of k1 and k2 or -1 if fails.
      Description: Finds the valid starting points of the flow. */
int neighbour(int n, node ***arr)
{
	int i1, i2, j1, j2, ct = 0, flag = 0, a, b,k2;
	int k = rand()%(n*n);
	while (ct < (n*n)){
		k %= (n*n);
		i1 = k/n;
		j1 = k%n;

		if (arr[i1][j1]->path_number==0)
		{
			int kk = rand()%4;
			int cc = 0;
			switch (kk)
			{
				case 0: i2= i1-1;
						j2= j1-0;
						if(i2>=0 && i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 1:	i2= i1-0;
						j2= j1-1;
						if(j2>=0 && i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 2: i2= i1+1;
						j2= j1-0;
						if(i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 3: i2= i1-0;
						j2= j1+1;
						if(i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;


				case 4: if(cc==4)
							break;
						i2= i1-1;
						j2= j1-0;
						if(i2>=0 && i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 5: if(cc==4)
							break;
						i2= i1-0;
						j2= j1-1;
						if(j2>=0 && i2<n && j2<n){
						if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 6: if(cc==4)
							break;
						i2= i1+1;
						j2= j1-0;
						if(i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;

				case 7: if(cc==4)
							break;
						i2= i1-0;
						j2= j1+1;
						if(i2<n && j2<n){
							if(arr[i2][j2]->path_number==0){
								flag=1;
								break;
							}
						}
						cc++;
			}
		}
		if(flag==1)
			break;

		ct++;
		k++;
	}

	if(ct<n*n){
		k2= (i2*n)+j2;
		return k*(n*n)+k2;
	}
	else{
		return -1;
	}
}
/************************/



/*    Name: checkneigh()
      Input: k1, k2, size of array row/column, 2D-array of pointers
      Output: returns 1 if true, 0 if fails.
      Description: Checks the neighbouring 4 vaues and find if there are more than 1 neighbours of the same set.
*/
int checkneigh(int k1, int k2, int n, node ***arr)
{
	int i= k2/n;
	int j= k2%n;
	int ii= k1/n;
	int jj= k1%n;

	int ct=0;
	if(i>0 && findset(arr[i-1][j])==findset(arr[ii][jj]))
		ct++;
	if(i<n-1 && findset(arr[i+1][j])==findset(arr[ii][jj]))
		ct++;
	if(j>0 && findset(arr[i][j-1])==findset(arr[ii][jj]))
		ct++;
	if(j<n-1 && findset(arr[i][j+1])==findset(arr[ii][jj]))
		ct++;

	if(ct>1)
		return 0;
	else
		return 1;
}
/****************************/




/*    Name: valid_next()
      Input: starting k, size of array row/column, 2D-array of pointers
      Output: returns the value of k2 or -1 if fails.
      Description: Finds the next valid points of the flow.
*/
int valid_next(int k, int n, node ***arr)
{
	int i1, i2, j1, j2, a, b, kk, stat,ct=0;
	int flag=0;
	i1= k/n;
	j1= k%n;
	kk= rand()%4;
	switch(kk)
	{
		case 0: i2= i1-1;
				j2= j1-0;
				if(i2>=0 && i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 1:	i2= i1-0;
				j2= j1-1;
				if(j2>=0 && i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 2: i2= i1+1;
				j2= j1-0;
				if(i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 3: i2= i1-0;
				j2= j1+1;
				if(i2<n && j2<n){
				if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;


		case 4: if(ct==4)
					break;
				i2= i1-1;
				j2= j1-0;
				if(i2>=0 && i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 5:	if(ct==4)
					break;
				i2= i1-0;
				j2= j1-1;
				if(j2>=0 && i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 6: if(ct==4)
					break;
				i2= i1+1;
				j2= j1-0;
				if(i2<n && j2<n){
					if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

		case 7: if(ct==4)
					break;
				i2= i1-0;
				j2= j1+1;
				if(i2<n && j2<n){
				if(arr[i2][j2]->path_number==0){
						stat= checkneigh(k, (n*i2 + j2),n,arr);
						//printf("%d\n",stat);
						if(stat){
							flag=1;
							break;
						}
					}
				}
				ct++;

	}
	//printf("flag- %d\n",flag);
	if(flag==0)
		return -1;
	if(flag){
		//printf("value sent- %d\n", i2*n + j2);
		return (i2*n)+j2;
	 }
}
/********************/





/*    Name: addpath()
      Input:  2D-array of pointers, size of array row/column, path number
      Output: returns 1 if a new path can be (or, is) added, 0 if not.
      Description: Creates a new flow path.
*/
int addpath(node ***arr, int n, int ptno)
{

	int a,b,k1,k2;
	int i1,j1,i2,j2;
	k2= neighbour( n, arr);

	if(k2==-1)         //no valid pair found to start with
		return 0;


	k1= k2/(n*n);
	k2= k2%(n*n);
	//printf("%d %d\n",k1,k2);

	i1= k1/n;
	j1= k1%n;
	i2= k2/n;
	j2= k2%n;
	//printf("%d %d\n",i1,j1);
	//printf("%d %d\n",i2,j2);

	//found i1,j1 and i2,j2
	arr[i1][j1]->endpoint= 1;

	arr[i2][j2]->path_number= ptno;
	arr[i1][j1]->path_number= ptno;


	node *n1, *n2;
	n1= arr[i1][j1];
	n2= arr[i2][j2];
	n1= findset(n1);
	n2= findset(n2);
	setunion(n1, n2);

	while(1){
		i1= i2;
		j1= j2;
		k1= (i1*n)+j1;

		/******/
		k2= valid_next(k1,n,arr);
		//printf("k2- %d\n",k2);

		if(k2==-1){
			arr[i1][j1]->endpoint= 1;
			break;
		}

		i2=k2/n;
		j2=k2%n;
		//printf("%d %d\n",i2,j2);
		arr[i2][j2]->path_number= ptno;
		node *n1, *n2;
		n1= arr[i1][j1];
		n2= arr[i2][j2];
		n1= findset(n1);
		n2= findset(n2);
		setunion(n1,n2);
	}
	return 1;
}
/************************/



/*    Name: printtable()
      Input:  2D-array of pointers, size of array row/column
      Output: --void--
      Description: Prints the question table and the corresponding solution table.
*/
void printtable(node ***arr, int n)
{
	int i,j;
	printf("Table to be solved:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(arr[i][j]->endpoint ==1){
				if(arr[i][j]->path_number/10==0)
					printf("| %d |",arr[i][j]->path_number);
				else
					printf("| %d|",arr[i][j]->path_number);
			}
			else if(arr[i][j]->path_number==0)
				printf("| X |");
			else
				printf("|   |");
		}
		printf("\n");
	}
	printf("\n\nThe solution to the above table:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(arr[i][j]->path_number != 0){
				if(arr[i][j]->path_number/10==0)
					printf("| %d |",arr[i][j]->path_number);
				else
					printf("| %d|",arr[i][j]->path_number);
			}
			else
				printf("| X |");
		}
		printf("\n");
	}

}
/******************/



/*    Name: main()
      Input:  --void--
      Output: returns 1
      Description: The driver function.
*/
int main(void)
{
	srand((unsigned int) time (NULL));
	int i, j;
	int ct = 1;

    // Size of board
	int n = 7;

	node*** pointers= (node ***)malloc(n*sizeof(node **));
	for (i=0; i<n; i++)
  		pointers[i] = (node **)malloc(n*sizeof(node *));

	initboard(pointers, n);


	while(1) {
		i = addpath(pointers, n, ct);
		if (i==0){
			//printf("Failure\n");
			break;
		}
		else {
			ct++;
			//printf("Success\n");
	    }
	}
	printtable(pointers,n);

	return 0;
}
/***********************/



