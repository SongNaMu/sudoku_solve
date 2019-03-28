#include <stdio.h>

int check_sudo();
int sol_sudo();
void print_sudo();
int check_arrN();

//sudo = sudoku
//空いている所は０を入れる
int sudo[9][9] ={{5,3,0,0,7,0,0,0,0},
				{6,0,0,1,9,5,0,0,0},
				{0,9,8,0,0,0,0,6,0},
				{8,0,0,0,6,0,0,0,3},
				{4,0,0,8,0,3,0,0,1},
				{7,0,0,0,2,0,0,0,6},
				{0,6,0,0,0,0,2,8,0},
				{0,0,0,4,1,9,0,0,5},
				{0,0,0,0,8,0,0,7,9}};

// arr1 ~ arr9はスドクの中の３＊３の小さいブロック
int *arr1[9], *arr2[9], *arr3[9], *arr4[9], *arr5[9], *arr6[9], *arr7[9], *arr8[9], *arr9[9];

//countNは空いているブロックの数　つまり０の数
int countN=0;


int main(){

	int count_0 =0;
	int i=0, j=0, k=0;
	int a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0,a8=0,a9=0;

	//このfor文で０の数を数えてcountNに入れる　！）後、関数に変える
	for(i=0; i<9;  i++)
			for(j=0; j<9; j++){
					if(sudo[i][j] == 0){
						//printf("arr[%d] = %d	arr[%d] = %d\n", count_0, arr[count_0], count_0, *arr[count_0]);
						count_0++;
					}
			}
	countN = count_0;
	
	//arr[]には０があるブロックの住所をいれる
	int *arr[count_0];
	count_0 = 0;
	//次のfor文でarr[]に０がある0ブロックの住所ををいれる
	//そしてarr1[]~arr2[]にもそれぞれの住所をいれる
	//！）後、関数に変える
			for(i=0; i<9;  i++)
					for(j=0; j<9; j++){
							if(sudo[i][j] == 0){
								arr[count_0] = &sudo[i][j];
								printf("arr[%d] = %d	*arr[%d] = %d\n", count_0, arr[count_0], count_0, *arr[count_0]);
								count_0++;
							}
							if(i>=0 && i<=2){
								if(j>=0 && j<=2){
									arr1[a1] = &sudo[i][j];
									a1++;
								}
								else if(j>=3 && j<=5){
									arr2[a2] = &sudo[i][j];
									a2++;
								}
								else{
									arr3[a3] = &sudo[i][j];
									a3++;
								}
							}
							else if(i>=3 && i<=5){
								if(j>=0 && j<=2){
									arr4[a4] = &sudo[i][j];
									a4++;
								}
								else if(j>=3 && j<=5){
									arr5[a5] = &sudo[i][j];
									a5++;
								}
								else{
									arr6[a6] = &sudo[i][j];
									a6++;
								}
							}
							else{
								if(j>=0 && j<=2){
									arr7[a7] = &sudo[i][j];
									a7++;
								}
								else if(j>=3 && j<=5){
									arr8[a8] = &sudo[i][j];
									a8++;
								}
								else{
									arr9[a9] = &sudo[i][j];
									a9++;
								}
							}
					}
	for(i=0; i<9; i++){
		printf("%d %d %d %d %d %d %d %d %d \n",*arr1[i],*arr2[i],*arr3[i],*arr4[i],*arr5[i],*arr6[i],*arr7[i],*arr8[i],*arr9[i]);
	}
	/*for(i=0; i<count_0; i++){
		printf("arr[%d] = %d  , %d\n",i, arr[i],*arr[i]);
	}*/
	//printf("sizeARR : %d",sizeof(arr)/8);
	printf("\n%d개 입니다.\n\n\n",count_0);
	print_sudo();
	printf("\n\n");
	sol_sudo(arr, 0);
	print_sudo();

	return 0;
}

//sudokuが完成してあるのかどうかを検査する関数
//sudokuに間違いがあるかどうかも検査する
int check_sudo(){
	//完成 return 2
	//未完成 return 1
	//間違いある return 0
	int result = 1;
	int i=0, j=0, k=0;
	int noZero = 0;

	//가로로 중복찾기
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			for(k=j+1; k<9; k++){
				if(sudo[i][k] == 0)
					noZero=1;
				if((sudo[i][j] == sudo[i][k])&&(sudo[i][j] != 0)&&(sudo[i][k] != 0)){
					//printf("오류 : sudo[%d][%d] = %d, sudo[%d][%d] = %d \n",i,j,sudo[i][j], i,k,sudo[i][k]);
					return 0;
				}
			}
		}
	}
	//세로로 중복찾기
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			for(k=j+1; k<9; k++){
					if((sudo[j][i] == sudo[k][i])&&(sudo[j][i] != 0)&&(sudo[k][i] != 0)){
						//printf("오류 : sudo[%d][%d] = %d, sudo[%d][%d] = %d \n",j,i,sudo[j][i], k,i,sudo[k][i]);
						return 0;
					}
			}
		}
	}


	if(check_arrN(arr1) || check_arrN(arr2) || check_arrN(arr3) ||
	check_arrN(arr4) || check_arrN(arr5) || check_arrN(arr6) ||
	check_arrN(arr7) || check_arrN(arr8) || check_arrN(arr9)){
		return 0;
	}

	if(noZero == 0)
		return 2;
	return 1;
}

int sol_sudo(int *arr[], int num){
	//마지막 자리 9까지 끝나거나 스도쿠 완성시 1
	//오류 있으면 0
	int i=0;
	int k=0;
	int check=-1;
	int check2=-1;
	int m=0, n=0;

	for(k = 1; k <= 9; k ++){

			*arr[num] = k;
			check = check_sudo();
			if(check == 1){
				//printf("오류 없음 %d \n",k);
	/*			for(m=0; m<9;  m++){
						for(n=0; n<9; n++){
									printf(" %d ",sudo[m][n]);
						}
						printf("\n");
				}*/
				check2=sol_sudo(arr, num+1);
				if(check2 == 1){
					break;
				}
				if(k == 9)
					*arr[num] = 0;
			}

			else if (check == 2){
				printf("스도쿠 완성\n");
				return 1;
			}

			else if (check == 0){
				*arr[num] = 0;
				//printf("오류로 번호 업 [%d] = %d, %d\n",num,k,k+1);
			}
			//printf("%d\n",check);
		}
}
//sudokuを見せる関数
void print_sudo(){
	int i, j;
	for(i=0; i<9;  i++){
			for(j=0; j<9; j++){
						printf(" %d ",sudo[i][j]);
						if(j%3 == 2)
							printf("|");
			}
			printf("\n");
			if(i%3 == 2)
				printf("------------------------------\n");
	}
}
//arr1~arr9の重複を確認する関数
int check_arrN(int *arr[]){
	int i=0, j=0;
	for(i=0; i<8; i++){
		for(j=i+1; j<9; j++){
			if((*arr[i] == *arr[j]) && (*arr[i] != 0))
				return 1;
		}
	}
	return 0;
}
