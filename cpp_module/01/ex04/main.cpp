/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:11:55 by sujilee           #+#    #+#             */
/*   Updated: 2022/04/19 16:59:44 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> // stream class header

void	replaceString(std::string &line, std::string s1, std::string s2)
{//line���� s1�� s2�� �ٲ��ش�.
	int	idx;

	while ((idx = line.find(s1)) != std::string::npos) // line���� s1���ڿ��� ã�Ƽ� �ε����� ��ȯ�Ѵ�.
	{
		line.erase(idx, s1.length()); // �ش� �ε������� s1���̸�ŭ �����ش�.
		line.insert(idx, s2); // �ش� �ε������� s2�� �����Ѵ�.
	}
	line += "\n";
}

int	main(int argc, char** argv)
{
	if (argc != 4 || argv[2][0] == 0)
		std::cout << "input error!" << std::endl;
	else
	{
		std::string		orgName = argv[1];
		std::ifstream	orgFile(orgName); // data�� ���ڿ��� �迭�� ���� �� �ּҸ� ��ȯ
		if (orgFile.is_open())
		{
			std::string		newName = orgName + ".replace";
			std::ofstream	newFile(newName); // ����� ������ �����Ѵ�.
			if (newFile.is_open())
			{
				std::string	line;
				while (std::getline(orgFile, line)) // �Է� ��Ʈ���� �޾� ���پ� �����´�.
				{
					replaceString(line, argv[2], argv[3]);
					newFile << line;
				}
				newFile.close();
			}
			else
				std::cout << "open error!" << std::endl;
			orgFile.close();
		}
		else
			std::cout << "open error!" << std::endl;
	}
	return (0);
}