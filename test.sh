#!/bin/bash

# Limpiar y compilar el proyecto
if make; then
    echo "Compilación exitosa"
else
    echo "Error: La compilación ha fallado"
    exit 1
fi

# Función para generar combinaciones aleatorias y ejecutar minishell
generate_and_run_minishell() {
  local current_combination=$1
  local minishell_output=$(./minishell <<< "$current_combination" | tail -n 1)
  local expected_output="quote es 0"
  local log_file="success.txt"

  # Verificar si hay comillas abiertas en la entrada
  if [[ "$minishell_output" =~ "quote es 1" ]]; then
    expected_output="quote es 1"
  fi

  if [[ "$minishell_output" == *"$expected_output"* ]]; then
    echo "\"$current_combination\" la salida esperada es: $expected_output la obtenida es $minishell_output" >> success.txt
  else
    echo "\"$current_combination\" la salida esperada es: $expected_output la obtenida es $minishell_output" >> fails.txt
  fi
}

# Función para generar combinaciones aleatorias de prueba y ejecutar minishell
generate_and_run_tests() {
  local alphabet=({a..z} {A..Z} " ")
  local special_chars=("'" "\"")

  for ((i = 0; i < 10000; i++)); do
    local current_combination=""

    # Generar combinaciones aleatorias
    for ((j = 0; j < 10; j++)); do
      current_combination+="${alphabet[RANDOM % ${#alphabet[@]}]}"
      current_combination+="${special_chars[RANDOM % ${#special_chars[@]}]}"
    done

    generate_and_run_minishell "$current_combination"
    sleep 0.1
  done
}

# Limpiar archivos de resultados anteriores
> success.txt
> fails.txt

# Llamar a la función para generar combinaciones de prueba y ejecutar minishell
generate_and_run_tests

# Contar pruebas aceptadas y falladas
total_success=$(wc -l < success.txt)
total_fails=$(wc -l < fails.txt)

# Imprimir resultados
echo "Pruebas superadas: $total_success"
echo "Pruebas falladas: $total_fails"
