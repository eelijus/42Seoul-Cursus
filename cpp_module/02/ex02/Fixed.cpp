/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:53:04 by sujilee           #+#    #+#             */
/*   Updated: 2022/05/03 10:55:44 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : fixedPoint(0) {
}

Fixed::Fixed(const int digit) {
	fixedPoint = digit << fracBits; // �Ҽ� ��Ʈ �κи�ŭ �о��ش�.
}

Fixed::Fixed(const float digit) {
	fixedPoint = (int)roundf(digit * (1 << fracBits)); // �����ο� �Ҽ� ��Ʈ��ŭ �����ش�.
}

Fixed::Fixed(const Fixed& ref) {
	*this = ref;
}

Fixed&	Fixed::operator=(const Fixed& ref) {
	fixedPoint = ref.fixedPoint;
	return *this;
}

bool	Fixed::operator>(const Fixed fixed) const {
	return (fixedPoint > fixed.fixedPoint);
}

bool	Fixed::operator<(const Fixed fixed) const {
	return (fixedPoint < fixed.fixedPoint);
}

bool	Fixed::operator>=(const Fixed fixed) const {
	return (fixedPoint >= fixed.fixedPoint);
}

bool	Fixed::operator<=(const Fixed fixed) const {
	return (fixedPoint <= fixed.fixedPoint);
}

bool	Fixed::operator==(const Fixed fixed) const {
	return (fixedPoint == fixed.fixedPoint);
}

bool	Fixed::operator!=(const Fixed fixed) const {
	return (fixedPoint != fixed.fixedPoint);
}

Fixed	Fixed::operator+(const Fixed fixed) const {
	return (Fixed(fixedPoint + fixed.fixedPoint));
}

Fixed	Fixed::operator-(const Fixed fixed) const {
	return (Fixed(fixedPoint - fixed.fixedPoint));
}

Fixed	Fixed::operator*(const Fixed fixed) const {
	return (Fixed(toFloat() * fixed.toFloat()));
}

Fixed	Fixed::operator/(const Fixed fixed) const {
	return (Fixed(toFloat() / fixed.toFloat()));
}

Fixed	Fixed::operator++() {
	fixedPoint += 1;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed	temp(*this);

	fixedPoint += 1;
	return temp;
}

Fixed	Fixed::operator--() {
	fixedPoint -= 1;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed	temp(*this);

	fixedPoint -= 1;
	return temp;
}

Fixed&	Fixed::min(Fixed& fixed1, Fixed& fixed2) {
	return (fixed1 <= fixed2 ? fixed1 : fixed2);
}

const Fixed&	Fixed::min(const Fixed& fixed1, const Fixed& fixed2) {
	return (fixed1 <= fixed2 ? fixed1 : fixed2);
}

Fixed&	Fixed::max(Fixed& fixed1, Fixed& fixed2) {
	return (fixed1 >= fixed2 ? fixed1 : fixed2);
}

const Fixed&	Fixed::max(const Fixed& fixed1, const Fixed& fixed2) {
	return (fixed1 >= fixed2 ? fixed1 : fixed2);
}

int		Fixed::getRawBits() const {
	return fixedPoint;
}

void	Fixed::setRawBits(int const raw) {
	fixedPoint = raw;
}

float	Fixed::toFloat() const {
	return (float)fixedPoint / (1 << fracBits);
}

int		Fixed::toInt() const {
	return fixedPoint >> fracBits; // �ٽ� �Ҽ� ��Ʈ��ŭ ��ܿ´�.
}

Fixed::~Fixed() {
}

std::ostream&	operator<<(std::ostream& outStream, const Fixed& fixed) {
	outStream << fixed.toFloat();
	return outStream;
}