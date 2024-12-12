#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Enum untuk status peminjaman buku
enum class BorrowStatus {
    Available,     // Buku tersedia
    Borrowed,      // Buku dipinjam
    Reserved       // Buku dipesan
};

// Enum untuk genre buku
enum class Genre {
    Action,
    Adventure,
    Drama,
    Fantasy,
    Horror,
    Romance,
    Comedy,
    Thriller,
    DarkFantasy,
    ScienceFiction,
    Mystery,
    Sports,
    Mecha
};

// Enum untuk type buku
enum class Type {
    Manga,
    Manhwa
};

// Fungsi untuk mengkonversi enum Genre ke string
string genreToString(Genre genre) {
    switch (genre) {
        case Genre::Action: return "Action";
        case Genre::Adventure: return "Adventure";
        case Genre::Drama: return "Drama";
        case Genre::Fantasy: return "Fantasy";
        case Genre::Horror: return "Horror";
        case Genre::Romance: return "Romance";
        case Genre::Comedy: return "Comedy";
        case Genre::Thriller: return "Thriller";
        case Genre::DarkFantasy: return "Dark Fantasy";
        case Genre::ScienceFiction: return "Sci-fi";
        case Genre::Mystery: return "Mystery";
        case Genre::Sports: return "Sports";
        case Genre::Mecha: return "Mecha";
        default: return "Unknown";
    }
}

// Fungsi untuk mengkonversi enum Type ke string
string typeToString(Type type) {
    return type == Type::Manga ? "Manga" : "Manhwa";
}

// Struct untuk menyimpan informasi buku
struct Book {
    string title;          // Judul buku
    string author;         // Pengarang buku
    int publicationYear;   // Tahun terbit buku
    BorrowStatus status;   // Status peminjaman buku
    Genre genre;           // Genre buku
    Type type;             // Type buku (Manga atau Manhwa)

    // Constructor untuk menginisialisasi buku
    Book(string t, string a, int year, BorrowStatus s, Genre g, Type ty) 
        : title(t), author(a), publicationYear(year), status(s), genre(g), type(ty) {}
};

// Fungsi untuk menambahkan buku ke dalam koleksi
void addBook(vector<Book*>& library, string title, string author, int publicationYear, BorrowStatus status, Genre genre, Type type) {
    // Alokasi memory untuk buku baru
    Book* newBook = new Book(title, author, publicationYear, status, genre, type);
    library.push_back(newBook);  // Menambahkan buku ke koleksi
}

// Fungsi untuk menghapus buku dari koleksi berdasarkan indeks
void removeBook(vector<Book*>& library, int index) {
    if (index < 0 || index >= library.size()) {
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }
    delete library[index];  // Menghapus buku dari memory
    library.erase(library.begin() + index);  // Menghapus buku dari vector
}

// Fungsi untuk mencari buku berdasarkan judul
int searchBookByTitle(const vector<Book*>& library, const string& title) {
    for (int i = 0; i < library.size(); ++i) {
        if (library[i]->title == title) {
            return i;  // Mengembalikan indeks buku yang ditemukan
        }
    }
    return -1;  // Buku tidak ditemukan
}

// Fungsi untuk mengurutkan buku berdasarkan tahun terbit
void sortBooksByYear(vector<Book*>& library) {
    sort(library.begin(), library.end(), [](Book* a, Book* b) {
        return a->publicationYear < b->publicationYear;
    });
}

// Kelas Library untuk mengelola perpustakaan
class Library {
private:
    vector<Book*> library;  // Koleksi buku dalam perpustakaan

public:
    // Menambahkan buku ke perpustakaan
    void addBook(string title, string author, int publicationYear, BorrowStatus status, Genre genre, Type type) {
        Book* newBook = new Book(title, author, publicationYear, status, genre, type);
        library.push_back(newBook);
    }

    // Menghapus buku dari perpustakaan berdasarkan judul
    void removeBook(string title) {
        int index = searchBookByTitle(title);
        if (index != -1) {
            delete library[index];
            library.erase(library.begin() + index);
        } else {
            cout << "Buku tidak ditemukan!" << endl;
        }
    }

    // Mencari buku berdasarkan judul
    int searchBookByTitle(string title) {
        for (int i = 0; i < library.size(); ++i) {
            if (library[i]->title == title) {
                return i;
            }
        }
        return -1;
    }

    // Mengurutkan buku berdasarkan tahun terbit
    void sortBooksByYear() {
        sort(library.begin(), library.end(), [](Book* a, Book* b) {
            return a->publicationYear < b->publicationYear;
        });
    }

    // Menampilkan semua buku di perpustakaan
    void displayBooks() {
        for (const auto& book : library) {
            cout << "Judul: " << book->title << ", Pengarang: " << book->author
                 << ", Tahun Terbit: " << book->publicationYear << ", Status: ";
            if (book->status == BorrowStatus::Available) {
                cout << "Tersedia";
            } else if (book->status == BorrowStatus::Borrowed) {
                cout << "Dipinjam";
            } else {
                cout << "Dipesan";
            }
            cout << ", Genre: " << genreToString(book->genre) << ", Type: " << typeToString(book->type) << endl;
        }
    }

    // Mendapatkan koleksi buku
    vector<Book*>& getLibrary() {
        return library;
    }
};

// Fungsi untuk menyimpan koleksi buku ke file biner
void saveLibraryToFile(const vector<Book*>& library, const string& filename) {
    ofstream file(filename, ios::out | ios::binary);
    for (const auto& book : library) {
        size_t titleLength = book->title.size();
        file.write(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));  // Menyimpan panjang judul
        file.write(book->title.c_str(), titleLength);  // Menyimpan judul buku

        size_t authorLength = book->author.size();
        file.write(reinterpret_cast<char*>(&authorLength), sizeof(authorLength));  // Menyimpan panjang pengarang
        file.write(book->author.c_str(), authorLength);  // Menyimpan pengarang buku

        file.write(reinterpret_cast<char*>(&book->publicationYear), sizeof(book->publicationYear));  // Menyimpan tahun terbit
        file.write(reinterpret_cast<char*>(&book->status), sizeof(book->status));  // Menyimpan status peminjaman
        file.write(reinterpret_cast<char*>(&book->genre), sizeof(book->genre));  // Menyimpan genre
        file.write(reinterpret_cast<char*>(&book->type), sizeof(book->type));  // Menyimpan type
    }
}

// Fungsi untuk memuat koleksi buku dari file biner
void loadLibraryFromFile(vector<Book*>& library, const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    while (file) {
        size_t titleLength;
        file.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
        if (!file) break;

        string title(titleLength, ' ');
        file.read(&title[0], titleLength);

        size_t authorLength;
        file.read(reinterpret_cast<char*>(&authorLength), sizeof(authorLength));

        string author(authorLength, ' ');
        file.read(&author[0], authorLength);

        int publicationYear;
        file.read(reinterpret_cast<char*>(&publicationYear), sizeof(publicationYear));

        BorrowStatus status;
        file.read(reinterpret_cast<char*>(&status), sizeof(status));

        Genre genre;
        file.read(reinterpret_cast<char*>(&genre), sizeof(genre));

        Type type;
        file.read(reinterpret_cast<char*>(&type), sizeof(type));

        library.push_back(new Book(title, author, publicationYear, status, genre, type));
    }
}

// Fungsi utama dengan input pengguna
int main() {
    Library myLibrary;

    myLibrary.addBook("One Piece", "Eiichiro Oda", 1997, BorrowStatus::Available, Genre::Adventure, Type::Manga);
    myLibrary.addBook("Attack on Titan", "Hajime Isayama", 2009, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Solo Leveling", "Chugong", 2018, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("My Hero Academia", "Kohei Horikoshi", 2014, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("The Breaker", "Jeon Geuk-jin", 2007, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("Naruto", "Masashi Kishimoto", 1999, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Dragon Ball", "Akira Toriyama", 1984, BorrowStatus::Available, Genre::Adventure, Type::Manga);
    myLibrary.addBook("Bleach", "Tite Kubo", 2001, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Fairy Tail", "Hiro Mashima", 2006, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("One Punch Man", "Yusuke Murata", 2009, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Tokyo Ghoul", "Sui Ishida", 2011, BorrowStatus::Available, Genre::Horror, Type::Manga);
    myLibrary.addBook("Fullmetal Alchemist", "Hiromu Arakawa", 2001, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Demon Slayer", "Koyoharu Gotouge", 2016, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Attack on Titan", "Hajime Isayama", 2009, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Death Note", "Tsugumi Ohba", 2003, BorrowStatus::Available, Genre::Mystery, Type::Manga);
    myLibrary.addBook("Sword Art Online", "Rei Kawahara", 2009, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Black Clover", "Yūki Tabata", 2015, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Hunter x Hunter", "Yoshihiro Togashi", 1998, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Blue Lock", "Muneyuki Kaneshiro", 2018, BorrowStatus::Available, Genre::Sports, Type::Manga);
    myLibrary.addBook("JoJo's Bizarre Adventure", "Hirohiko Araki", 1987, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Vinland Saga", "Makoto Yukimura", 2005, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Berserk", "Kentaro Miura", 1989, BorrowStatus::Available, Genre::DarkFantasy, Type::Manga);
    myLibrary.addBook("Shingeki no Kyojin", "Hajime Isayama", 2009, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("The Rising of the Shield Hero", "Aneko Yusagi", 2012, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Overlord", "Kugane Maruyama", 2010, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("No Game No Life", "Yuu Kamiya", 2012, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Bleach", "Tite Kubo", 2001, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Naruto Shippuden", "Masashi Kishimoto", 2007, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Fruits Basket", "Natsuki Takaya", 1998, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Attack on Titan", "Hajime Isayama", 2009, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("March Comes in Like a Lion", "Chica Umino", 2007, BorrowStatus::Available, Genre::Drama, Type::Manga);
    myLibrary.addBook("The Promised Neverland", "Kaiu Shirai", 2016, BorrowStatus::Available, Genre::Mystery, Type::Manga);
    myLibrary.addBook("Your Lie in April", "Naoshi Arakawa", 2011, BorrowStatus::Available, Genre::Drama, Type::Manga);
    myLibrary.addBook("Kaguya-sama: Love is War", "Aka Akasaka", 2015, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("The Quintessential Quintuplets", "Negi Haruba", 2017, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Re:Zero", "Tappei Nagatsuki", 2012, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Goblin Slayer", "Kumo Kagyu", 2016, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Log Horizon", "Mamare Touno", 2010, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("That Time I Got Reincarnated as a Slime", "Fuse", 2013, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Cautious Hero", "Light Tuchihi", 2016, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("The Seven Deadly Sins", "Nakaba Suzuki", 2012, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Dr. Stone", "Riichiro Inagaki", 2017, BorrowStatus::Available, Genre::ScienceFiction, Type::Manga);
    myLibrary.addBook("Food Wars!", "Yūto Tsukuda", 2012, BorrowStatus::Available, Genre::Comedy, Type::Manga);
    myLibrary.addBook("Gintama", "Hideaki Sorachi", 2004, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Love Hina", "Ken Akamatsu", 1998, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Angel Beats!", "Jun Maeda", 2010, BorrowStatus::Available, Genre::Drama, Type::Manga);
    myLibrary.addBook("Nisekoi", "Naoshi Komi", 2011, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Hunter X Hunter", "Yoshihiro Togashi", 1998, BorrowStatus::Available, Genre::Adventure, Type::Manga);
    myLibrary.addBook("The Ancient Magus' Bride", "Kore Yamazaki", 2013, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Slam Dunk", "Takehiko Inoue", 1990, BorrowStatus::Available, Genre::Sports, Type::Manga);
    myLibrary.addBook("Boku no Hero Academia", "Kohei Horikoshi", 2014, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Tokyo Ghoul:re", "Sui Ishida", 2014, BorrowStatus::Available, Genre::Horror, Type::Manga);
    myLibrary.addBook("Kingdom", "Yasuhisa Hara", 2006, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Promised Neverland", "Kaiu Shirai", 2016, BorrowStatus::Available, Genre::Thriller, Type::Manga);
    myLibrary.addBook("D.Gray-man", "Katsura Hoshino", 2004, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Toradora!", "Yuyuko Tokemiya", 2006, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Angel Beats!", "Jun Maeda", 2010, BorrowStatus::Available, Genre::Drama, Type::Manga);
    myLibrary.addBook("Yona of the Dawn", "Mizuho Kusanagi", 2009, BorrowStatus::Available, Genre::Romance, Type::Manga);
    myLibrary.addBook("Sword Art Online: Progressive", "Rei Kawahara", 2012, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("The King of Fighters", "Hiroshi Matsumoto", 1994, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Fate/stay night", "Type-Moon", 2004, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Witchcraft Works", "Ryu Mizunagi", 2010, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Tokyo Revengers", "Ken Wakui", 2017, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Triage X", "Shouji Sato", 2010, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Noragami", "Adachitoka", 2011, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Black Clover", "Yūki Tabata", 2015, BorrowStatus::Available, Genre::Fantasy, Type::Manga);
    myLibrary.addBook("Fate/Zero", "Gen Urobuchi", 2006, BorrowStatus::Available, Genre::Action, Type::Manga);
    myLibrary.addBook("Noblesse", "Son Jeho", 2007, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("The God of High School", "Yongje Park", 2011, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("Tower of God", "S.I.U", 2010, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("God of Blackfield", "Ryu Ki-Woon", 2016, BorrowStatus::Available, Genre::Action, Type::Manhwa);
    myLibrary.addBook("Wind Breaker", "Jo Yongseok", 2017, BorrowStatus::Available, Genre::Sports, Type::Manhwa);


    // User input untuk memilih aksi
    while (true) {
        cout << "\n=== Menu ===\n";
        cout << "1. Lihat Daftar Buku\n";
        cout << "2. Tambah Buku\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Simpan ke File\n";
        cout << "5. Muat dari File\n";
        cout << "6. Keluar\n";
        cout << "Pilih tindakan: ";
        
        int choice;
        cin >> choice;
        cin.ignore();  // Untuk menghindari masalah input setelah memilih

        if (choice == 1) {
            myLibrary.displayBooks();
        } else if (choice == 2) {
            string title, author;
            int year, genreChoice, typeChoice;
            cout << "Masukkan judul buku: ";
            getline(cin, title);
            cout << "Masukkan pengarang buku: ";
            getline(cin, author);
            cout << "Masukkan tahun terbit: ";
            cin >> year;
            // Menampilkan pilihan genre
            cout << "Pilih genre:\n";
            cout << "0 - Action\n";
            cout << "1 - Adventure\n";
            cout << "2 - Drama\n";
            cout << "3 - Fantasy\n";
            cout << "4 - Horror\n";
            cout << "5 - Romance\n";
            cout << "6 - Comedy\n";
            cout << "7 - Thriller\n";
            cout << "8 - Dark Fantasy\n";
            cout << "9 - Science Fiction\n";
            cout << "10 - Mystery\n";
            cout << "11 - Sports\n";
            cout << "12 - Mecha\n";
            cout << "Masukkan pilihan genre (0-12): ";
            cin >> genreChoice;
            cout << "Pilih type (0-Manga, 1-Manhwa): ";
            cin >> typeChoice;
            myLibrary.addBook(title, author, year, BorrowStatus::Available, static_cast<Genre>(genreChoice), static_cast<Type>(typeChoice));
        } else if (choice == 3) {
            string title;
            cout << "Masukkan judul buku yang ingin dihapus: ";
            cin.ignore();  // Membersihkan input buffer
            getline(cin, title);
            myLibrary.removeBook(title);
        } else if (choice == 4) {
            saveLibraryToFile(myLibrary.getLibrary(), "../data/library.dat");
            cout << "Data telah disimpan!" << endl;
        } else if (choice == 5) {
            loadLibraryFromFile(myLibrary.getLibrary(), "../data/library.dat");
            cout << "Data telah dimuat!" << endl;
        } else if (choice == 6) {
            break;
        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    }

    return 0;
}
