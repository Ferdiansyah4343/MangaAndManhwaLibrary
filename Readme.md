
# Proyek Manajemen Buku Manga/Manhwa

Proyek ini adalah aplikasi manajemen perpustakaan digital untuk manga dan manhwa. Pengguna dapat memilih genre buku, menambah, menghapus, dan melihat daftar buku berdasarkan genre yang dipilih.

## Fitur

- Menambahkan buku baru ke dalam perpustakaan
- Menghapus buku dari perpustakaan
- Menampilkan buku berdasarkan genre yang dipilih
- Mendukung genre seperti Action, Adventure, Drama, Fantasy, Horror, Romance, dan lainnya
- Mendukung tipe buku seperti Manga dan Manhwa
- Memungkinkan pengguna untuk memilih genre yang diinginkan

## Genre Buku

Berikut adalah beberapa genre buku yang dapat dipilih:

- Action
- Adventure
- Drama
- Fantasy
- Horror
- Romance
- Comedy
- Thriller
- Dark Fantasy
- Science Fiction
- Mystery
- Sports
- Mecha

## Cara Menggunakan

1. **Kloning repositori ini**:
   ```bash
   $ git clone https://github.com/Ferdiansyah4343/MangaAndManhwaLibrary.git
   $ cd MangaAndManhwaLibrary
   ```

2. **Kompilasi kode C++**:
   ```bash
   $ g++ -o ./bin/MangaAndManhwaLibrary MangaAndManhwaLibrary.cpp
   ```

3. **Jalankan program**:
   ```bash
   $ cd bin
   $ ./library_program
   ```


## Struktur Program

- **Genre**: Enum untuk genre buku (Action, Adventure, dll.)
- **Book**: Struktur untuk menyimpan informasi buku
- **Library**: Kelas untuk mengelola buku dalam perpustakaan
- **Fungsi utama**: Menampilkan menu dan menangani input pengguna untuk memilih genre, menambah buku, dan menghapus buku.

### Pembuat

Proyek ini dibuat oleh Ferdiansyah Pratama sebagai bagian dari pembelajaran pengembangan perangkat lunak menggunakan C++.

### Lisensi

Proyek ini dilisensikan di bawah [Nama Lisensi] - lihat [LICENSE](LICENSE) untuk informasi lebih lanjut.
