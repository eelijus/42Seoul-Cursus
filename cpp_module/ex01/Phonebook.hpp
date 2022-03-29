/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:28:51 by sujilee           #+#    #+#             */
/*   Updated: 2022/03/29 14:50:16 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

#include "Contact.hpp"

class PhoneBook {
	private: 
			Contact contact[8];
			int		currIdx;
	public:
			//Ư���� �޼ҵ�. ������
			PhoneBook();
			void		ShowPhoneBook();
			void		AddContact();
			void		SearchIndex();
			std::string ShortenString(std::string str);
			//Ư���� �޼ҵ�. �Ҹ���
			~PhoneBook();
};

#endif
