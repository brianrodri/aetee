#pragma once
#include <SFML/Keyboard.hpp>

class KeyCodeListener {

    using KeySequence = std::vector<sf::Keyboard::Key>;
    using Callback = std::function<void()>;

public:

    template <typename InputIt>
        //requires Same<sf::Keyboard::Key, ValueType<InputIt>>
    void registerCombo(InputIt keyBegin, InputIt keyEnd, Callback f)
    {
        if (std::distance(keyBegin, keyEnd) > 0) {
            comboList.emplace_back(keyBegin, keyEnd);
            comboProgress.push_back(std::begin(list_iter.back()));
            comboCallback.push_back(f);
        }
    }

    void resetAll()
    {
        auto list_iter = std::begin(comboList);
        auto progress_iter = std::begin(comboProgress);

        while (list_iter != std::end(comboList)) {
            *progress_iter++ = std::begin(*list_iter++);
        }
    }

    void operator()(sf::Keyboard::Key keyCode)
    {
        auto list_iter = std::begin(comboList);
        auto progress_iter = std::begin(comboProgress);
        auto callback_iter = std::begin(comboCallback);

        while (list_iter != std::end(comboList)) {
            auto& curCombo = *list_iter++;
            auto& curProgressIter = *progress_iter++;
            auto& curCallback = *callback_iter++;

            // Check if the key matches the next key the combo under consideration requires
            if (*curProgressIter == keyCode) {
                ++curProgressIter; // Move onto next key

                // Unless that was the last key, in which case...
                if (curProgressIter == std::end(curCombo)) {
                    curCallback();
                    resetAll();
                    break;
                }
            } else {
                // An incorrect key was pressed, so we need to start from scratch
                curProgressIter = std::begin(curCombo);
            }
        }
    }

private:

    std::vector<KeySequence>  comboList;
    std::vector<KeySequence::iterator>  comboProgress;
    std::vector<Callback> comboCallback;

} /*class KeyCodeListener*/;


using namespace sf::Keyboard;
std::initializer_list<Key> kickSequence = {Key::K};
std::initializer_list<Key> punchSequence = {Key::P};
std::initializer_list<Key> uppercutSequence = {Key::Left, Key::Down, Key::P};
std::initializer_list<Key> energyBlastSequence = {Key::Down, Key::Right, Key::Down, Key::Right, Key::P};

KeyCodeListener guyComboListener{};
guyComboListener.registerCombo(std::begin(kickSequence), std::end(kickSequence), doGuyKick);
guyComboListener.registerCombo(std::begin(punchSequence), std::end(punchSequence), doGuyPunch);
guyComboListener.registerCombo(std::begin(uppercutSequence), std::end(uppercutSequence), doGuyUppercut);
guyComboListener.registerCombo(std::begin(energyBlastSequence), std::end(energyBlastSequence), doGuyEnergyBlast);

while (window.pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed) {
        guyComboListener(event.key.code);
    }
}
