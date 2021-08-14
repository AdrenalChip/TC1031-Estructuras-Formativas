/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>

long sum_seq(int n) {
	long acum=0;
	for (int i=1;i<=n;i++){
		acum+= i;
	}
	return acum;
}

long sum_rec(int n) {
	if (n<=1){
		return 1;
	}else{
		return n+(sum_rec(n-1));
	}
}

long fact_seq(int n) {
	long fact=1;
	if (n<=0){
		return -1;
	}
	for (int i=1;i<=n;i++){
		fact*=1;
	}
	return fact;
}

long fact_rec(int n) {
	if (n<=0){
		return -1;
	}else if (n==1){
		return 1;
	}else{
		return n*fact_rec(n-1);
	}
}

long fib_seq(int n) {
	long a,b, aux;
	int i;
	if (n==1 || n==2){
		return 1;
	}
	a=1;
	b=1;
	i=3;
	while (i<=n){
		aux=a+b;
		a=b;
		b=aux;
		i++;
	}
	return b;
}

long fib_rec(int n) {
	if (n==1 || n==2){
		return 1;
	}else{
		return (fib_rec(n-1)+ fib_rec(n-2));
	}
}

long gcd_seq(long a, long b) {
	long aux;
	while (b != 0){
		aux=b;
		b= a%b;
		a=aux;
	}
	return a;
}

long gcd_rec(long a, long b) {
	if (b==0){
		return a;
	}else{
		return gcd_rec(b,a%b);
	}
}

bool find_seq(int arr[], int size, int val) {
	for (int i=0;i < size;i++){
		if (val==arr[i]){
			return true;
		}
	}
	return false;
}

bool find_rec(int arr[], int low, int high, int val) {
	int mid;
	bool aux;
	if (((high - low)+1)==1){
		return (val==arr[low]);
	}else {
		aux=false;
		mid = (high+low)/2;
		aux = find_rec(arr,low,mid,val);
		if (!aux){
			aux=find_rec(arr,mid+1,high,val);
		}
		return aux;
	}
}

int max_seq(int arr[], int size) {
	return 0;
}

int max_rec(int arr[], int low, int high) {
	return 0;
}

int unimodal_seq(int arr[], int size) {
	return 0;
}

int unimodal_rec(int arr[], int low, int high) {
	return 0;
}

int unimodal_rec(int arr[], int size) {
	return 0;
}

int bs_seq(int arr[], int size, int val) {
	return 0;
}

int bs_aux(int arr[], int low, int high, int val) {
	return 0;
}

int bs_rec(int arr[], int size, int val) {
	return 0;
}
#endif /* RECURSION_H_ */
