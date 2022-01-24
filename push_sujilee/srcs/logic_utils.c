/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 22:06:47 by sujilee           #+#    #+#             */
/*   Updated: 2022/01/22 20:50:21 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pivoting_a(t_carrier *carrier, t_stack **a, t_stack **b, int pivot)
{
	t_stack *head;

	while (carrier->arem_cnt > 0)
	{
		head = *a;
		if (head->data <= pivot)
		{
			pb(carrier, a, b);
			//carrier->pb_num++;
			carrier->pa_num++;
			carrier->brem_cnt++;
		}
		else
		{
			ra(a);
			carrier->rra_num++;
		}
		carrier->arem_cnt--;
	}
}

void	pivoting_b(t_carrier *carrier, t_stack **a, t_stack **b, int pivot)
{
	t_stack *head;
	
	while (carrier->brem_cnt > 0)
	{
		head = *b;
		if (head->data <= pivot)
		{
			pa(carrier, a, b);
			carrier->pa_num--;
			carrier->arem_cnt++;
		}
		else
		{
			rb(b);
			carrier->rrb_num++;
		}
		carrier->brem_cnt--;
	}
}

void	attach_unsorted(t_carrier *carrier, t_stack **a, t_stack **b, char c)
{
 	t_stack *t;

	t = (t_stack*)malloc(sizeof(t_stack) * 1);
	if (t == 0)
	{
		while (carrier->a_remnant != 0)
		{
			t = carrier->a_remnant;
			carrier->a_remnant = carrier->a_remnant->next;
			free(t);
		}
		while (carrier->b_remnant != 0)
		{
			t = carrier->b_remnant;
			carrier->b_remnant = carrier->b_remnant->next;
			free(t);
		}
	}
	t->data = c == 'a' ? carrier->rra_num : carrier->rrb_num;
	t->next = c == 'a' ? carrier->a_remnant : carrier->b_remnant;
	if (c == 'a')
		carrier->a_remnant = t;
	else
		carrier->b_remnant = t;

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