#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Livro {
public:
    string titulo;
    string autor;
    int copiasDisponiveis;

    Livro(const string& titulo, const string& autor, int copiasDisponiveis)
        : titulo(titulo), autor(autor), copiasDisponiveis(copiasDisponiveis) {}

    static void AdicionarLivro(const string& titulo, const string& autor, int copiasDisponiveis) {
        livros.push_back(Livro(titulo, autor, copiasDisponiveis));
    }

    static bool VerificarDisponibilidade(const string& titulo) {
        for (const Livro& livro : livros) {
            if (livro.titulo == titulo && livro.copiasDisponiveis > 0) {
                return true;
            }
        }
        return false;
    }

    static bool RegistrarEmprestimo(const string& titulo, const string& usuario) {
        for (Livro& livro : livros) {
            if (livro.titulo == titulo && livro.copiasDisponiveis > 0) {
                emprestimos[usuario].push_back(titulo);
                livro.copiasDisponiveis--;
                return true;
            }
        }
        return false;
    }

    static vector<string> LivrosEmprestadosPorUsuario(const string& usuario) {
        if (emprestimos.find(usuario) != emprestimos.end()) {
            return emprestimos[usuario];
        }
        return {};
    }

private:
    static vector<Livro> livros;
    static map<string, vector<string>> emprestimos;
};

vector<Livro> Livro::livros;
map<string, vector<string>> Livro::emprestimos;

class Usuario {
public:
    string nome;

    Usuario(const string& nome) : nome(nome) {}
};

int main() {
    Livro::AdicionarLivro("Livro A", "Autor A", 3);
    Livro::AdicionarLivro("Livro B", "Autor B", 2);
    Livro::AdicionarLivro("Livro C", "Autor C", 1);

    Livro::RegistrarEmprestimo("Livro A", "Usuario 1");
    Livro::RegistrarEmprestimo("Livro A", "Usuario 2");
    Livro::RegistrarEmprestimo("Livro B", "Usuario 1");

    bool disponivel = Livro::VerificarDisponibilidade("Livro A");
    if (disponivel) {
        cout << "Livro A está disponível." << endl;
    } else {
        cout << "Livro A não está disponível." << endl;
    }

    vector<string> livrosEmprestados = Livro::LivrosEmprestadosPorUsuario("Usuario 1");
    cout << "Livros emprestados por Usuario 1: ";
    for (const string& livro : livrosEmprestados) {
        cout << livro << " ";
    }
    cout << endl;

    return 0;
}
