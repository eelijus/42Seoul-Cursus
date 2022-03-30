/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:11:00 by sujilee           #+#    #+#             */
/*   Updated: 2022/03/30 17:36:03 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int		main()
{
	//const char *�� ���ڷ� �� string ��ü ������ �ڵ� ȣ��
	Zombie zombieKing("sujilee");
	//���ÿ� ����ƴٰ� main()�� return�� ������ �Ҹ��� ȣ��
	zombieKing.announce();

	Zombie *zombieKnight = newZombie("kchoi");	
	//���� �Ҵ�ƴٰ�
	zombieKnight->announce();
	//���⼭ �����ǰ� �Ҹ��� ȣ��
	delete zombieKnight;

	//�Լ� ������ ��������(����)�� ��ü�� �����ߴٰ� �Լ� ��ȯ �� ��ü �Ҹ��� ȣ��
	randomChump("Faker");
	
	return (0);
	
}