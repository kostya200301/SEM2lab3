#ifndef SEN2LAB2_IMAP_H
#define SEN2LAB2_IMAP_H

#include <iostream>
#include <vector>
#include "Sequence.h"
#include "ArraySequence.h"
#include "DynamicArray.h"
#include "malloc.h"
#include <string.h>


template <typename K, typename V>
class IMap {
private:
    Sequence<K>* keys;
    Sequence<Sequence<V>*>* values;
public:
    IMap() {
        keys = new ArraySequence<K>();
        values = new ArraySequence<Sequence<V>*>();
    };

    ~IMap() {
        this->keys->~Sequence();
        this->values->~Sequence();
    }

    IMap(const IMap& map) {
        this->keys = map.keys;
        this->values = map.values;
    }

    //IMap(Sequence<K>* keys, Sequence<Sequence<V>*>* values);

    Sequence<V>* GetElementsByKey(K key) {
        for (int i = 0; i < keys->GetLength(); i++) {
            if (memcmp(&key, &(keys->Get(i)), sizeof(key)) == 0) {
                return values->Get(i);
            }
        }
        Sequence<V>* sec = new ArraySequence<V>();
        return sec;
    }

    void SetValueByKey(K key, V value, int (*cmpK)(K,K), bool OnlyOne=0, bool repetition=1, int (*cmpV)(V,V)=NULL) {
        for (int i = 0; i < keys->GetLength(); i++) {
            if (cmpK(key, keys->Get(i))) {
                if (!OnlyOne){ // Добавляем только если для этого ключа может быть несколько значений
                    if (repetition){
                        values->Get(i)->Append(value); // Если доступны повторения добавляем в любом случае
                    }
                    else {
                        bool in = 1;
                        if (cmpV == NULL) {
                            throw "Invalid cmp for Values";
                        }
                        for (int k = 0; k < values->Get(i)->GetLength(); k++) {
                            if (cmpV(value, values->Get(i)->Get(k))) {
                                in = 0;
                            }
                        }
                        if (in) {
                            values->Get(i)->Append(value);
                        }
                    }
                }
                return;
            }
        }
        keys->Append(key);
        Sequence<V>* sec = new ArraySequence<V>();
        sec->Append(value);
        values->Append(sec);
    }

    void ReplaceValueByKey(K key, V value) {
        for (int i = 0; i < keys->GetLength(); i++) {
            if (memcmp(&key, &(keys->Get(i)), sizeof(key)) == 0) {
                values->Get(i)->Set(value, 0);
                return;
            }
        }
        keys->Append(key);
        Sequence<V>* sec = new ArraySequence<V>();
        sec->Append(value);
        values->Append(sec);
    }

    void Print() {
        for (int i = 0; i < keys->GetLength(); i++) {
            cout << keys->Get(i) << ": {";
            for (int j = 0; j < values->Get(i)->GetLength() - 1; j++) {
                cout << values->Get(i)->Get(j) << ", ";
            }
            if (values->Get(i)->GetLength() - 1 >= 0) {
                cout << values->Get(i)->Get(values->Get(i)->GetLength() - 1) << "";
            }
            cout << "}\n";
        }
    }


    vector<pair<K, int>> GetVectorKeyCount() {
        vector<pair<K, int>> v;
        for (int i = 0; i < keys->GetLength(); i++) {
            v.push_back({keys->Get(i), values->Get(i)->GetLength()});
        }
        return v;
    }

    vector<pair<K, Sequence<V>*>> GetVectorKeyElements() {
        vector<pair<K, Sequence<V>*>> v;
        for (int i = 0; i < keys->GetLength(); i++) {
            v.push_back({keys->Get(i), values->Get(i)});
        }
        return v;
    }

};


#endif //SEN2LAB2_IMAP_H
