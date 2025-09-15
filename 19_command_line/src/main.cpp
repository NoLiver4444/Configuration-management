#include <gtkmm.h>

class ConsoleWindow : public Gtk::Window {
public:
    ConsoleWindow();
    
protected:
    // Виджеты
    Gtk::Box m_main_box;
    Gtk::TextView m_text_view;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::Entry m_input_entry;
    Glib::RefPtr<Gtk::TextBuffer> m_text_buffer;
};

ConsoleWindow::ConsoleWindow() {
    // Настройка окна
    set_title("Эмулятор командной строки");
    set_default_size(800, 600);
    
    // Главный контейнер
    m_main_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(m_main_box);
    
    // Текстовое поле для вывода
    m_text_buffer = Gtk::TextBuffer::create();
    m_text_view.set_buffer(m_text_buffer);
    m_text_view.set_editable(false);
    m_text_view.set_cursor_visible(false);
    m_text_view.set_wrap_mode(Gtk::WRAP_WORD_CHAR);
    
    // Настраиваем моноширинный шрифт для консоли
    auto font = Pango::FontDescription("Monospace 12");
    m_text_view.override_font(font);
    
    m_scrolled_window.add(m_text_view);
    m_scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_main_box.pack_start(m_scrolled_window, Gtk::PACK_EXPAND_WIDGET);
    
    // Поле ввода
    m_input_entry.set_placeholder_text("Введите команду...");
    m_main_box.pack_start(m_input_entry, Gtk::PACK_SHRINK);
    
    // Показываем все виджеты
    show_all();
    
    // Фокус на поле ввода
    m_input_entry.grab_focus();
}

int main(int argc, char* argv[]) {
    // Инициализация GTK
    auto app = Gtk::Application::create(argc, argv, "com.example.console");
    
    // Создание и запуск окна
    ConsoleWindow window;
    
    // Показываем окно и запускаем приложение
    return app->run(window);
}