# Problema 393A Python

En este link esta como se define el problema [Problem - 393A Nineteen](https://codeforces.com/contest/393/problem/A "Nineteen")  

aqui vamos a explicar como se resolvio el problema.  

se ingresa una palabra o string, se sabe que la palabra nineteen tiene 3 vecees n, 3 veces e, 1 vez t y 1 vez i pero la palabra puede estar desordenada en la palabra que se ingresa, por lo que hay que contar una cantidad de n, e, t y i que se repitan en la palabra y ver cuantas veces se debe formar la palabra y tengo una variable infinito por que se debe tomar la menor cantidad de veces que se forma la palabra nineteen con las letras de la palabra.

```python
palabra = input()
nineteen= {'n' : 3,'e':3,'t':1,'i':1}
n_repetido = float('inf')
```
la palabra se separa letra por letra en una lista llamada letras_palabra, para luego identificar las letras unicas de la palabra, despues se cuenta cada letra unica en la palabra y se agrega a un diccionario con la tupla de valores la letra unica y las veces que se repite en la palabra
```python
letras_palabra= list(palabra)
letras_unicas=set(palabra)

numero_veces = map(lambda x: letras_palabra.count(x),letras_unicas)

dic_palabra = dict(zip(letras_unicas,list(numero_veces)))
```
ahora vemos las veces que se puede repetir nineteen, contando que tambien se puede contar nineteenineteen habiendo 5 n por lo que se puede expresar numero de veces que aparece n-1/2, si aparece 3 veces se puede formar 1 vez la palabra si las otras condiciones lo favorecen, pero necesita 5 para formarse dos veces, 7 para formarse 3 veces y asi, los otros si necesitan aparecer un multiplo de veces y se toma la menor cantidad que puede aparecer la palabra o 0 si no aparece alguna letra de nineteen.
```python
for i in nineteen.keys():
	if(i in dic_palabra):
		veces_rletra = i == 'n' and (dic_palabra[i]-1)//(nineteen[i]-1) or dic_palabra[i]//nineteen[i]
		if(n_repetido >= veces_rletra):
			n_repetido = veces_rletra
	else:
		n_repetido = 0
		break
print(n_repetido)
```