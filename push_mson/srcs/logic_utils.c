/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:15:22 by sujilee           #+#    #+#             */
/*   Updated: 2022/01/20 13:44:14 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pivoting_a(t_carrier *carrier, t_stack **a, t_stack **b, int pivot)
{
	t_stack *head;
	int		count;
	t_stack *curr;


	count = carrier->arem_cnt;
	carrier->rra_num = 0;
	printf("[pivition_a] in\n");

	head = *a;
	curr = head;
	//{ �Ǻ����� �۰ų� ���� ���� pb & arem_cnt-- & pb_num++}
	while (count--)
	{
		printf("curr->data : %d <= pivot : %d\n", curr->data, pivot);
		if (curr->data <= pivot)
		{
			pb(carrier, a, b);
			carrier->brem_cnt++;
			carrier->arem_cnt--;
			carrier->pb_num++;
		}
		//{ �Ǻ����� ũ�ٸ� ra & rra_num++ (�����ĵ� ������ �ٽ� rra�� �÷�����ϴϱ�)}
		else
		{
			ra(a);
			carrier->rra_num++;
		}
		curr = curr->next;
	}
}

void	pivoting_b(t_carrier *carrier, t_stack **a, t_stack **b, int pivot)
{
	t_stack *head;
	
		printf("[pivition_b] in\n");


	carrier->rrb_num = 0;
	head = *b;
	//{ �Ǻ����� �۰ų� ���� ���� pa & brem_cnt-- & pa_num++}
	if (head->data <= pivot)
	{
		pa(carrier, a, b);

	}
	//{ �Ǻ����� ũ�ٸ� rb & rrb_num++ (�����ĵ� ���� �ٽ� rrb�� �÷�����ϴϱ�)}
	else
	{
		rb(b);

	}	
}

void	attach_unsorted(t_carrier *carrier, t_stack **a, t_stack **b, char c)
{
    t_stack *unsorted;

	printf("[attach_unsorted] in");

    unsorted = (t_stack *)malloc(sizeof(t_stack));
	if (!unsorted)
    {
        free_stack(&(carrier->a_remnant));
        free_stack(&(carrier->b_remnant));
    }    
    if (c == 'a')
    {
        unsorted->data = carrier->rra_num;
        unsorted->next = carrier->a_remnant;
        carrier->a_remnant = unsorted;
        return ;
    }
    unsorted->data = carrier->rrb_num;
    unsorted->next = carrier->b_remnant;
    carrier->b_remnant = unsorted;
    
}

void	handle_one_two_a(t_carrier *carrier, t_stack **a, t_stack **b)
{
	t_stack *b_head;
	t_stack *head;

	//���� b_remnant ���Ḯ��Ʈ �� ���� �ִ� ���� free���ٰ���
	//�� ������ �׸��� ���� b_head�� �����
	b_head = carrier->b_remnant;
	if (b_head)
	{
		//brem_cnt�� ���� 1 Ȥ�� 2�� �ܷ������� �Ҵ� 
		carrier->brem_cnt = carrier->b_remnant->data;
		//b_remnant�� ����Ű�� headNode�� �ι�°�� �ٲ��ִ� 
		carrier->b_remnant = carrier->b_remnant->next;
	}
	//������ ���� (�ѵΰ�¥��)b_head�� free
	free(b_head);
	
	head = *a;
	//���� 1�� ���
	if (carrier->arem_cnt == 1)
	{
		ra(a);
		carrier->arem_cnt = 0;
		return ;
	}
	//���� 2�� ���
	if (head->data > head->next->data)
		sa(a);
	ra(a);
	ra(a);
	carrier->arem_cnt = 0;
}

void	handle_one_two_b(t_carrier *carrier, t_stack **a, t_stack **b)
{
	t_stack *a_head;
	t_stack *head;


	carrier->pa_num -= carrier->brem_cnt;
	carrier->arem_cnt = carrier->a_remnant->data;

	a_head = carrier->a_remnant;
	carrier->a_remnant = carrier->a_remnant->next;
	free(a_head); 

	head = *b;
	//b�� unsorted ž ������ 1�϶�
	if (carrier->brem_cnt == 1)
	{
		pa(carrier, a, b);
		ra(a);
		carrier->brem_cnt = 0;
		return ;
	}
	//b�� unsorted ž ������ 2�϶�
	if (head->data < head->next->data)
		sb(b);
	pa(carrier, a, b);
	pa(carrier, a, b);
	ra(a);
	ra(a);
	carrier->brem_cnt = 0;
}