palabra = input()
nineteen= {'n' : 3,'e':3,'t':1,'i':1}
n_repetido = float('inf')

letras_palabra= list(palabra)
letras_unicas=set(palabra)

numero_veces = map(lambda x: letras_palabra.count(x),letras_unicas)

dic_palabra = dict(zip(letras_unicas,list(numero_veces)))

for i in nineteen.keys():
	if(i in dic_palabra):
		veces_rletra = i == 'n' and (dic_palabra[i]-1)//(nineteen[i]-1) or dic_palabra[i]//nineteen[i]
		if(n_repetido >= veces_rletra):
			n_repetido = veces_rletra
	else:
		n_repetido = 0
		break
print(n_repetido)