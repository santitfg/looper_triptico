#!/bin/bash

# Ruta de la carpeta que contiene las imágenes
input_folder="./litio3"
output_folder="./img1"

# Crear la carpeta de salida si no existe
mkdir -p "$output_folder"

# Recorrer todas las imágenes en la carpeta de entrada
for img in "$input_folder"/*.{png,jpg,jpeg}; do
    # Obtener el nombre del archivo sin la ruta
    filename=$(basename "$img")

    # Voltear la imagen 90 grados (de vertical a horizontal o viceversa)
    mogrify -path "$output_folder" -rotate 90 "$img"

    #echo "Imagen $filename volteada y guardada en $output_folder"
done

echo "Proceso completado."
