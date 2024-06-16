/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Factory.hpp
*/

#ifndef SEAL_FACTORY_HPP
    #define SEAL_FACTORY_HPP

class Factory {
public:
    template<typename Element, typename... Args>
    static std::shared_ptr<Element> createElement(Args&&... args)
    {
        return std::make_shared<Element>(std::forward<Args>(args)...);
    }
};

#endif //SEAL_FACTORY_HPP
