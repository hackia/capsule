//
// Created by hackia on 10/2/25.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
using namespace std;

namespace {
    enum class Parent {
        Cpp,
        Python,
        Java,
        Rust,
    };

    class Capsule {
    public:
        Capsule() = default;

        Capsule *use(const Parent &p);


        Capsule *withName(const string &n);

        Capsule *withVersion(const string &v);

        Capsule *withDescription(const string &d);

        Capsule *withAuthor(const string &a);

        Capsule *withLicense(const string &l);

        Capsule *withUpstream(const string &u);

        Capsule *captureEchoForInstall(const string &echo);

        Capsule *captureEchoForUninstall(const string &echo);

        Capsule *captureEchoForTests(const string &echo);

        Capsule *captureInstallSource(const string &source);

        Capsule *captureUninstallSource(const string &source);

        Capsule *captureRunForInstall(const string &command);

        Capsule *captureRunForUninstall(const string &command);

        Capsule *captureRunForTests(const string &command);

        [[nodiscard]] string getName() const;

        [[nodiscard]] string getVersion() const;

        [[nodiscard]] string getDescription() const;

        [[nodiscard]] string getAuthor() const;

        [[nodiscard]] string getLicense() const;

        [[nodiscard]] string getUpstream() const;

        [[nodiscard]] string getInstallSource() const;

        [[nodiscard]] string getUninstallSource() const;

        [[nodiscard]] vector<string> getEchoForInstall() const;

        [[nodiscard]] vector<string> getEchoForUninstall() const;

        [[nodiscard]] vector<string> getEchoForTests() const;

        [[nodiscard]] vector<string> getRunForInstall() const;

        [[nodiscard]] vector<string> getRunForUninstall() const;

        [[nodiscard]] vector<string> getRunForTests() const;

        static string extractSourceDirectory(const std::string &url, const std::string &version);

        void print() const;

    private:
        Parent parent;
        string name;
        string version;
        string description;
        string author;
        vector<string> run_install;
        vector<string> run_uninstall;
        vector<string> run_tests;
        string license;
        string upstream;
        string install_source;
        string uninstall_source;
        vector<string> echo_install;
        vector<string> echo_tests;
        vector<string> echo_uninstall;
    };

    Capsule *Capsule::use(const Parent &p) {
        this->parent = p;
        return this;
    }

    Capsule *Capsule::withName(const string &n) {
        this->name.clear();
        this->name = n;
        return this;
    }

    Capsule *Capsule::withVersion(const string &v) {
        this->version.clear();
        this->version = v;
        return this;
    }

    Capsule *Capsule::withDescription(const string &d) {
        this->description.clear();
        this->description = d;
        return this;
    }

    Capsule *Capsule::withAuthor(const string &a) {
        this->author.clear();
        this->author = a;
        return this;
    }

    Capsule *Capsule::withLicense(const string &l) {
        this->license.clear();
        this->license = l;
        return this;
    }

    Capsule *Capsule::withUpstream(const string &u) {
        this->upstream.clear();
        this->upstream = u;
        return this;
    }

    Capsule *Capsule::captureEchoForInstall(const string &echo) {
        this->echo_install.push_back(echo);
        return this;
    }

    Capsule *Capsule::captureEchoForUninstall(const string &echo) {
        this->echo_uninstall.push_back(echo);
        return this;
    }

    Capsule *Capsule::captureEchoForTests(const string &echo) {
        this->echo_tests.push_back(echo);
        return this;
    }

    Capsule *Capsule::captureInstallSource(const string &source) {
        this->install_source.clear();
        this->install_source = source;
        return this;
    }

    Capsule *Capsule::captureUninstallSource(const string &source) {
        this->uninstall_source.clear();
        this->uninstall_source = source;
        return this;
    }

    Capsule *Capsule::captureRunForInstall(const string &command) {
        this->run_install.push_back(command);
        return this;
    }

    Capsule *Capsule::captureRunForUninstall(const string &command) {
        this->run_uninstall.push_back(command);
        return this;
    }

    Capsule *Capsule::captureRunForTests(const string &command) {
        this->run_tests.push_back(command);
        return this;
    }

    string Capsule::getName() const {
        return this->name;
    }

    string Capsule::getVersion() const {
        return this->version;
    }

    string Capsule::getDescription() const {
        return this->description;
    }

    string Capsule::getAuthor() const {
        return this->author;
    }

    string Capsule::getLicense() const {
        return this->license;
    }

    string Capsule::getUpstream() const {
        return this->upstream;
    }

    string Capsule::getInstallSource() const {
        return this->install_source;
    }

    string Capsule::getUninstallSource() const {
        return this->uninstall_source;
    }

    vector<string> Capsule::getEchoForInstall() const {
        return this->echo_install;
    }

    vector<string> Capsule::getEchoForUninstall() const {
        return this->echo_uninstall;
    }

    vector<string> Capsule::getEchoForTests() const {
        return this->echo_tests;
    }

    vector<string> Capsule::getRunForInstall() const {
        return this->run_install;
    }

    vector<string> Capsule::getRunForUninstall() const {
        return this->run_uninstall;
    }

    vector<string> Capsule::getRunForTests() const {
        return this->run_tests;
    }

    string Capsule::extractSourceDirectory(const std::string &url, const std::string &version) {
        const size_t last_slash_before_archive = url.rfind("/archive/");
        if (last_slash_before_archive == std::string::npos) {
            return "";
        }

        const size_t project_start = url.rfind('/', last_slash_before_archive - 1);
        if (project_start == std::string::npos) {
            return "";
        }

        const std::string project_name = url.substr(project_start + 1,
                                                    last_slash_before_archive - project_start - 1);

        // Return format: /project-version
        return "/" + project_name + "-" + version;
    }

    void Capsule::print() const {
        cout << "Name: " << this->getName() << endl;
        cout << "Version: " << this->getVersion() << endl;
        cout << "Description: " << this->getDescription() << endl;
        cout << "Author: " << this->getAuthor() << endl;
        cout << "License: " << this->getLicense() << endl;
        cout << "Upstream: " << this->getUpstream() << endl;
        cout << "Install Source: " << this->getInstallSource() << endl;
        cout << "Uninstall Source: " << this->getUninstallSource() << endl;
        cout << "Echo for Install: " << endl;
        for (const auto &echo: this->getEchoForInstall()) {
            cout << echo << endl;
        }
        cout << "Echo for Uninstall: " << endl;
        for (const auto &echo: this->getEchoForUninstall()) {
            cout << echo << endl;
        }
        cout << "Echo for Tests: " << endl;
        for (const auto &echo: this->getEchoForTests()) {
            cout << echo << endl;
        }
        cout << "Run for Install: " << endl;
        for (const auto &run: this->getRunForInstall()) {
            cout << run << endl;
        }
        cout << "Run for Uninstall: " << endl;
        for (const auto &run: this->getRunForUninstall()) {
            cout << run << endl;
        }
        cout << "Run for Tests: " << endl;
        for (const auto &run: this->getRunForTests()) {
            cout << run << endl;
        }

        cout << endl;
    }
}

int main(const int argc, const char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }
    const std::filesystem::path input_file = argv[1];
    if (input_file.extension() != ".capsule") {
        std::cerr << "Input file must be a .capsule file" << std::endl;
        return 1;
    }
    if (std::ifstream file(argv[1]); file.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        Capsule capsule{};
        bool in_install = false;
        bool in_uninstall = false;
        bool in_tests = false;
        string source;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            if (line == "@install") {
                in_install = true;
                in_uninstall = false;
                in_tests = false;
                continue;
            }
            if (line == "@uninstall") {
                in_install = false;
                in_uninstall = true;
                in_tests = false;
                continue;
            }
            if (line == "@test") {
                in_install = false;
                in_uninstall = false;
                in_tests = true;
                continue;
            }
            if (line == "@end") {
                in_install = false;
                in_uninstall = false;
                in_tests = false;
                continue;
            }

            // Check if line starts with whitespace (spaces or tabs)
            if (!line.empty() && (line[0] == ' ' || line[0] == '\t')) {
                // Remove all leading whitespace
                size_t first_non_space = line.find_first_not_of(" \t");
                if (first_non_space == string::npos) {
                    continue; // Line is all whitespace
                }
                line = line.substr(first_non_space);

                if (line.starts_with("@echo ")) {
                    string echo_content = line.substr(6); // Skip "@echo "
                    if (in_install) {
                        capsule.captureEchoForInstall(echo_content);
                    } else if (in_uninstall) {
                        capsule.captureEchoForUninstall(echo_content);
                    } else if (in_tests) {
                        capsule.captureEchoForTests(echo_content);
                    }
                }

                if (line.starts_with("@run ")) {
                    string command = line.substr(5); // Skip "@run "
                    if (in_tests) {
                        capsule.captureRunForTests(command);
                    } else if (in_install) {
                        capsule.captureRunForInstall(command);
                    } else if (in_uninstall) {
                        capsule.captureRunForUninstall(command);
                    }
                }

                if (line.starts_with("@unmount-src") && !line.contains("https://") && in_uninstall) {
                    if (source.empty()) {
                        std::cerr << "Source not found for @unmount-src" << std::endl;
                        return 1;
                    }
                    capsule.captureUninstallSource(source);
                }
                if (line.starts_with("@mount-src ") && line.contains("https://") && in_install) {
                    source = line.substr(11); // Skip "@mount-src "
                    capsule.captureInstallSource(source);
                }
                continue;
            }
            if (line[0] == '@' && line.contains("use")) {
                if (line.contains("cpp")) {
                    capsule.use(Parent::Cpp);
                } else if (line.contains("rust")) {
                    capsule.use(Parent::Rust);
                } else if (line.contains("python")) {
                    capsule.use(Parent::Python);
                } else if (line.contains("java")) {
                    capsule.use(Parent::Java);
                }
            } else if (line.starts_with("@name ")) {
                capsule.withName(line.substr(6));
            } else if (line.starts_with("@version ")) {
                capsule.withVersion(line.substr(9));
            } else if (line.starts_with("@description ")) {
                capsule.withDescription(line.substr(13));
            } else if (line.starts_with("@author ")) {
                capsule.withAuthor(line.substr(8));
            } else if (line.starts_with("@license ")) {
                capsule.withLicense(line.substr(9));
            } else if (line.starts_with("@upstream ")) {
                capsule.withUpstream(line.substr(10));
            }
        }
        capsule.print();
        std::cout << "Source directory: " << Capsule::extractSourceDirectory(
            capsule.getInstallSource(), capsule.getVersion()) << std::endl;
        return 0;
    }
    std::cerr << "Failed to open " << input_file << std::endl;
    return 1;
}
