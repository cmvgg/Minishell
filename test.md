Pasos:		|		Test:
234:		|		-Escribir en archivo externo
234:		|		-Si no válido archivo vacío
  3:		|		-Comprobar Diff los espacios con comando correcto
  3:		|		-Separar los token por "\n"
  3:		|		-Comando y Argumentos en la misma línea
  3:		|		-Si es un alias comprobar que se escribe el comando completo
  4:		|		-Solo redirecciones en orden
  5:		|		-Separar por pipes "\n" "-" "\n"
678:		|		-Si es Built-in o comando, escribir en archivo Built Comando
 67:		|		-Si no es Built-in o comando, escribir en archivo Probar
  8:		|		-Si no es Archivo, escribir en archivo error
 10:		|		-Salida a Succes y comparar con bash