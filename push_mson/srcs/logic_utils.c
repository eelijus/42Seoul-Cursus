/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:15:22 by sujilee           #+#    #+#             */
/*   Updated: 2022/01/18 19:19:13 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pivoting_a(t_carrier *carrier, t_stack **a, t_stack **b, int pivot)
{
	t_stack *head;

	printf("[pivition_a] in\n");

	carrier->rra_num = 0;
	head = *a;
	//{ �Ǻ����� �۰ų� ���� ���� pb & arem_cnt-- & pb_num++}
	if (head->data <= pivot)
	{
		pb(carrier, a, b);
		carrier->arem_cnt--;
		carrier->pb_num++;
		carrier->brem_cnt++;
	}
	//{ �Ǻ����� ũ�ٸ� ra & rra_num++ (�����ĵ� ������ �ٽ� rra�� �÷�����ϴϱ�)}
	else
	{
		ra(a);
		carrier->rra_num++;
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
		carrier->brem_cnt--;
		carrier->pa_num++;
	}
	//{ �Ǻ����� ũ�ٸ� rb & rrb_num++ (�����ĵ� ���� �ٽ� rrb�� �÷�����ϴϱ�)}
	else
	{
		rb(b);
		carrier->rrb_num++;
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
	t_stack *head;
	int max;
	int min;
	
	head = *a;
	max = find_max(carrier, a, 'a');
	min = find_min(carrier, a, 'a');
	//pa_num == 1 �� ���
	if (carrier->pa_num == 1)
	{
		//{ra}
		ra(a);
		return ;
	}
	//pa_num == 2 �� ���
	else if (carrier->pa_num == 2)
	{
		handle_two_a(carrier, a, b, min);
		return ;
	}
	printf("[handle_one_two_a] in\n");
}


void    handle_two_a(t_carrier *carrier, t_stack **a, t_stack **b, int min)
{
	t_stack *head;

	printf("[handle_two_a] in\n");


	head = *a;
	//{top == min�̸� ra, ra}
	if (head->data == min)
	{
		ra(a);
		ra(a);
	}
//{top != min�̸� sa, ra, ra}
	else
	{
		sa(a);
		ra(a);
		ra(a);
	}
}

void    handle_one_b(t_carrier *carrier, t_stack **a, t_stack **b)
{

	printf("[handle_one_b] in\n");


    pb(carrier, a, b);
	carrier->pa_num--;
	carrier->pb_num++;

}

void    handle_two_b(t_carrier *carrier, t_stack **a, t_stack **b, int min)
{

		printf("[handle_two_b] in\n");

    //{top == min�̸� pa, pa -> ra, ra}
	if ((*a)->data == min)
	{
		pa(carrier, a, b);
		pa(carrier, a, b);
		ra(a);
		ra(a);
		carrier->brem_cnt -= 2;
		carrier->pa_num += 2;
	}
    //{top != min�̸� sb, pa, pa -> ra, ra}
	else
	{
		sb(b);
		pa(carrier, a, b);
		pa(carrier, a, b);
		ra(a);
		ra(a);
		carrier->brem_cnt -= 2;
		carrier->pa_num += 2;
	}
}

void	handle_one_two_b(t_carrier *carrier, t_stack **a, t_stack **b)
{
	t_stack *head;
	int max;
	int min;
	
	printf("[handle_one_two_b] in\n");


	head = *a;
	max = find_max(carrier, b, 'b');
	min = find_min(carrier, b, 'b');
//pb_num == 1 �� ���
	if (carrier->pb_num == 1)
	{
		handle_one_b(carrier, a, b);
	}
//pb_num == 2 �� ���
	else if (carrier->pb_num == 2)
	{
		handle_two_b(carrier, a, b, min);
	}
}