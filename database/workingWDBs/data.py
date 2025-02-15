import sqlite3
import csv

def csv_to_sqlite(csv_file, db_file, table_name):
    """Imports a CSV file into an SQLite database."""
    conn = sqlite3.connect(db_file)
    cursor = conn.cursor()
    
    with open(csv_file, 'r', newline='', encoding='utf-8') as file:
        reader = csv.reader(file)
        headers = next(reader)  # Read column names
        
        cursor.execute(f'DROP TABLE IF EXISTS {table_name}')
        cursor.execute(f'CREATE TABLE {table_name} ({", ".join([f"{col} TEXT" for col in headers])})')
        
        for row in reader:
            placeholders = ', '.join(['?'] * len(row))
            cursor.execute(f'INSERT INTO {table_name} VALUES ({placeholders})', row)
    
    conn.commit()
    conn.close()
