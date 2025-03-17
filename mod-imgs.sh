#!/bin/bash

# Ruta de la carpeta que contiene las imágenes
input_folder="./render_litio5"
output_folder="./img3"

# Crear la carpeta de salida si no existe
mkdir -p "$output_folder"

# Recorrer todas las imágenes en la carpeta de entrada
for img in "$input_folder"/*.png; do
    # Obtener el nombre del archivo sin la ruta
    filename=$(basename "$img")

    # Voltear la imagen 90 grados (de vertical a horizontal)
    # Redimensionar a 1080x640 y guardar en formato JPG con calidad media
    mogrify -path "$output_folder" -format jpg -quality 85 -rotate 90 -resize 1080x640 "$img"

    echo "Imagen $filename procesada y guardada en $output_folder"
done

echo "Proceso completado."
