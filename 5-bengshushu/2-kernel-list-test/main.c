#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct num{
	int i;
	struct list_head list;
};

int main()
{
	struct num *num;
	struct num *num1;
	int i;

	LIST_HEAD(test_list);
	
	/*初始化内核链表的实验*/
	for(i = 0;i < 100;i ++){
		num = (struct num*)malloc(sizeof(struct num));
		num->i = i;
		list_add_tail(&num->list,&test_list);
	}

	/*打印成员的值*/
	i = 0;
	list_for_each_entry(num,&test_list,list){
		printf("%3d ",num->i);
		if((i+1)%10==0)
			printf("\n");
		i++;
	}

	printf("\n");

	list_for_each_entry_safe(num,num1,&test_list,list){
		list_del(&num->list);
		free(num);
	}

    if(list_empty(&test_list)){
		printf("free test list successfully\n");
	}

	return 0;
}
