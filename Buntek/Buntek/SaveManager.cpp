#include "SaveManager.h"
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <map>
#include <iostream>

namespace JSON {
    struct Value;

    struct ValueData {
        map<string, Value> subObject;
        string string;
        int number = 0;
    };

    struct Value {
        ValueData data;

        Value& operator[](string name) {
            return data.subObject[move(name)];
        }

        const Value& operator[](string name) const {
            auto it = data.subObject.find(move(name));

            if (it != data.subObject.end()) {
                return it->second;
            }

            throw;
        }

        Value& operator=(string value) {
            data.string = value;
            return *this;
        }

        Value& operator=(double value) {
            data.number = value;
            return *this;
        }
    };

    template<typename T> T& asAny(Value&);
    template<typename T> const T& asAny(const Value&);

    template<>
    extern int& asAny<int>(Value& value) {
        return value.data.number;
    }

    template<>
    extern const int& asAny<int>(const Value& value) {
        return value.data.number;
    }

    template<>
    extern const string& asAny<string>(const Value& value) {
        return value.data.string;
    }

    template<>
    extern string& asAny<string>(Value& value) {
        return value.data.string;
    }
};

// sequence for
template <typename T, T... S, typename F>
constexpr void for_sequence(integer_sequence<T, S...>, F&& f) {
    using unpack_t = int[];
    (void)unpack_t {
        (static_cast<void>(f(integral_constant<T, S>{})), 0)..., 0
    };
}

template<typename Class, typename T>
struct PropertyImpl {
    constexpr PropertyImpl(T Class::* aMember, const char* aName) : member{ aMember }, name{ aName } {}

    using Type = T;

    T Class::* member;
    const char* name;
};

// One could overload this function to accept both a getter and a setter instead of a member.
template<typename Class, typename T>
constexpr auto property(T Class::* member, const char* name) {
    return PropertyImpl<Class, T>{member, name};
}


// unserialize function
template<typename T>
T fromJson(const JSON::Value& data) {
    T object;

    // We first get the number of properties
    constexpr auto nbProperties = tuple_size<decltype(T::properties)>::value;

    // We iterate on the index sequence of size `nbProperties`
    for_sequence(make_index_sequence<nbProperties>{}, [&](auto i) {
        // get the property
        constexpr auto property = get<i>(T::properties);

        // get the type of the property
        using Type = typename decltype(property)::Type;

        // set the value to the member
        object.*(property.member) = JSON::asAny<Type>(data[property.name]);
        });

    return object;
}

template<typename T>
JSON::Value toJson(const T& object) {
    JSON::Value data;

    // We first get the number of properties
    constexpr auto nbProperties = tuple_size<decltype(T::properties)>::value;

    // We iterate on the index sequence of size `nbProperties`
    for_sequence(make_index_sequence<nbProperties>{}, [&](auto i) {
        // get the property
        constexpr auto property = get<i>(T::properties);

        // set the value to the member
        data[property.name] = object.*(property.member);
        });

    return data;
}

namespace animal {

    struct Dog {
        std::string barkType;
        std::string color;
        int weight = 0;

        bool operator==(const Dog& rhs) const {
            return barkType == rhs.barkType && color == rhs.color && weight == rhs.weight;
        }

        constexpr static auto properties = std::make_tuple(
            property(&Dog::barkType, "barkType"),
            property(&Dog::color, "color"),
            property(&Dog::weight, "weight")
        );
    };
}

_saveManager* _saveManager::instance = 0;

_saveManager::_saveManager()
{
}

_saveManager::~_saveManager()
{
}

_saveManager& _saveManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _saveManager();
    return *instance;
}

void _saveManager::SaveData(void)
{
    animal::Dog dog;

    dog.color = "green";
    dog.barkType = "whaf";
    dog.weight = 30;

    JSON::Value jsonDog = toJson(dog); // produces {"color":"green", "barkType":"whaf", "weight": 30}
    auto dog2 = fromJson<animal::Dog>(jsonDog);

    std::cout << std::boolalpha << (dog == dog2) << std::endl; // pass the test, both dog are equal!
}

void _saveManager::LoadData(void)
{

}
