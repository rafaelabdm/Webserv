#!/usr/bin/env python

import os
import urllib.parse
import sys

translation_dict = {
    'hello': 'oi',
    'world': 'mundo',
    'good': 'bom',
    'morning': 'manhã',
    'evening': 'tarde',
    'night': 'noite',
    'how': 'como',
    'are': 'está',
    'you': 'você',
    'today': 'hoje',
    'beautiful': 'bonito',
    'friend': 'amigo',
    'thank': 'obrigado',
    'please': 'por favor',
    'help': 'ajuda',
    'yes': 'sim',
    'no': 'não',
    'I': 'eu',
    'love': 'amo',
    'this': 'isso',
    'language': 'idioma',
    'learning': 'aprendendo',
    'new': 'novo',
    'words': 'palavras',
    'in': 'em',
    'my': 'meu',
    'dictionary': 'dicionário'
}

def translate_text(text, translation_dict):
    words = text.split()
    translated_words = [translation_dict.get(word, word) for word in words]
    translated_text = ' '.join(translated_words)
    return translated_text

def main():
    if os.environ['REQUEST_METHOD'] != 'POST':
        return
    query_string = os.environ['REQUEST_BODY']
    text = urllib.parse.parse_qs(query_string)
    translated_text = translate_text(text["input"][0].lower(), translation_dict)
    print(f"<p>Translated text: {translated_text}</p>")


print('<!DOCTYPE html>')
print('<html lang="en">')
print('<head>')
print('<meta charset="UTF-8">')
print('<meta name="viewport" content="width=device-width, initial-scale=1.0">')
print('<title>Translator</title>')
print('</head>')
print('<body>')
print('<h1>A Very Poor Translator</h1>')
print('<form action="translator.py" method="post">')
print('<label for="text-input">Enter Text To Translate:</label>')
print('<input type="text" id="text-input" name="input" required>')
print('<br>')
print('<input type="submit" value="Submit">')
print('</form>')
main()
print('</body>')
print('</html>')
