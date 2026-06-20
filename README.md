# Dosya 1 — Binary File Generator (Console)

**Author:** M. Emre TURHAN (meturhan@hotmail.com) | Student ID: 051213082  
**Year:** ~2008–2009  
**Language:** C++ (Visual C++ 2005)  
**Platform:** Windows Console Application  
**Project:** Visual Studio 2005 (`.vcproj`)

## Overview

A C++ console application that generates structured binary data files from a format specification. It reads a text-based format definition file, parses field descriptions, and generates random binary records with fixed-width fields for direct-access file operations.

This is one of four companion tools in the binary file management suite:
- **dosya-1-generator** (this repo) — generates binary data files
- [dosya-oku-reader](https://github.com/meturhan/dosya-oku-reader) — reads/display records from binary data files
- [rafige-random-generator](https://github.com/meturhan/rafige-random-generator) — C# version of the generator
- [fivi-file-viewer](https://github.com/meturhan/fivi-file-viewer) — C# file viewer using RaFiGe's format reader

## How It Works

### Command-Line Usage
```
Dosya_1.exe <format_file> <data_file> <record_count>
```

| Argument | Description |
|----------|-------------|
| `format_file` | Path to the format specification text file (e.g., `format_file.txt`) |
| `data_file` | Path for the output binary data file (e.g., `data_file.dat`) |
| `record_count` | Number of records to generate |

### Format Specification File

The format file defines the structure of each record using CSV-like lines:

```
Gamer,String,10,4-6,"******"
Score,Integer,5,10000-1000000
Date,String,10,"2008****##"
```

Each line contains:
| Field | Example | Description |
|-------|---------|-------------|
| Name | `Gamer` | Field name |
| Type | `String` or `Integer` | Data type |
| Size | `10` | Byte size in the record (fixed-width) |
| Range | `4-6` | Min-max random length (for strings) or value range (for integers) |
| Pattern | `"******"` | Format pattern: `*` = random alphanumeric, `#` = random digit, literal = fixed character |

If a field has no range, `y-o-k` is written in that position. If no pattern, `y-o-k` is written.

### Data Generation Algorithm

The program processes each field sequentially:

1. **Parse the format file** into a matrix (`form[20][5]`)
2. **Calculate record size** by summing all field byte sizes
3. **For each field, generate data for all records:**

#### String Fields
- A random string is generated of length between `minRange` and `maxRange`
- If a format pattern is specified (`"******"`):
  - `*` → random alphanumeric character (digit, uppercase, or lowercase)
  - `#` → random digit (0-9)
  - Any other character → used as-is (fixed)
  - If the string is shorter than the pattern, only the first N patterned chars are generated
- If no pattern, completely random ASCII characters are generated
- The string is padded with spaces to fill the fixed field width
- Written byte-by-byte to the correct record position using `fseek`

#### Integer Fields
- A random integer is generated within the specified range
- Written at the correct record position
- If the field size is larger than `sizeof(int)` (4 bytes), leading bytes are filled with spaces
- Integer is written as raw binary via `fwrite(&randInt, sizeof(int), 1, d)`

### Record Layout

Records are stored contiguously in the binary file. Each record has a fixed width equal to the sum of all field sizes. Direct access to record N is computed as:
```
record_offset = N * record_size + field_offset
```

## Key Functions

| Function | Purpose |
|----------|---------|
| `ListeyeEkle(string str)` | Parses a format line into the field matrix |
| `kayitAlaniHesapla()` | Calculates total record byte size |
| `stringUret(min, max, formatSpec)` | Generates random string per format pattern |
| `random(min, max)` | Generates random integer in range |
| `dosyayaYaz(data_file, kacKayit, kayitAlani)` | Writes all records to the binary file |

## Example

With the sample format file and `Dosya_1.exe format_file.txt data_file.dat 10`, the program generates:
- 10 records, each containing: Gamer (String, 10 bytes), Score (Integer, 5 bytes), Date (String, 10 bytes)
- Each record = 10 + 5 + 10 = **25 bytes**
- Total file size = 10 × 25 = **250 bytes**

## How to Build

Open `Dosya_1.sln` in Visual Studio 2005. Build in either Debug or Release configuration. The project uses precompiled headers (`stdafx.h`/`stdafx.cpp`).
