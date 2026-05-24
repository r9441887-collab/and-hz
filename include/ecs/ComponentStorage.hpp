#pragma once
#include <vector>
#include <functional>
#include <cassert>
#include "Entity.hpp"

template<typename T>
class ComponentStorage {
public:
    ComponentStorage() = default;
    ~ComponentStorage() = default;

    ComponentStorage(const ComponentStorage&) = delete;
    ComponentStorage& operator=(const ComponentStorage&) = delete;

    ComponentStorage(ComponentStorage&&) = default;
    ComponentStorage& operator=(ComponentStorage&&) = default;

    void add(Entity entity, T&& component) {
        uint32_t idx = getEntityIndex(entity);
        if (idx < sparse_.size() && sparse_[idx] != ENTITY_NULL) {
            data_[sparseEntryToIndex(sparse_[idx])] = std::move(component);
            return;
        }
        if (idx >= sparse_.size()) {
            sparse_.resize(idx + 1, ENTITY_NULL);
        }
        dense_.push_back(entity);
        data_.push_back(std::move(component));
        sparse_[idx] = static_cast<Entity>(dense_.size() - 1);
    }

    void remove(Entity entity) {
        uint32_t idx = getEntityIndex(entity);
        if (idx >= sparse_.size() || sparse_[idx] == ENTITY_NULL) return;

        uint32_t denseIdx = sparseEntryToIndex(sparse_[idx]);
        Entity lastEntity = dense_.back();

        dense_[denseIdx] = lastEntity;
        data_[denseIdx] = std::move(data_.back());

        uint32_t lastIdx = getEntityIndex(lastEntity);
        if (lastIdx < sparse_.size()) {
            sparse_[lastIdx] = sparse_[idx];
        }

        dense_.pop_back();
        data_.pop_back();
        sparse_[idx] = ENTITY_NULL;
    }

    T& get(Entity entity) {
        uint32_t idx = getEntityIndex(entity);
        assert(idx < sparse_.size() && sparse_[idx] != ENTITY_NULL);
        return data_[sparseEntryToIndex(sparse_[idx])];
    }

    const T& get(Entity entity) const {
        uint32_t idx = getEntityIndex(entity);
        assert(idx < sparse_.size() && sparse_[idx] != ENTITY_NULL);
        return data_[sparseEntryToIndex(sparse_[idx])];
    }

    bool has(Entity entity) const {
        uint32_t idx = getEntityIndex(entity);
        return idx < sparse_.size() && sparse_[idx] != ENTITY_NULL;
    }

    void forEach(std::function<void(Entity, T&)> callback) {
        for (size_t i = 0; i < dense_.size(); ++i) {
            callback(dense_[i], data_[i]);
        }
    }

    void forEach(std::function<void(Entity, const T&)> callback) const {
        for (size_t i = 0; i < dense_.size(); ++i) {
            callback(dense_[i], data_[i]);
        }
    }

    size_t size() const { return dense_.size(); }

    void clear() {
        sparse_.clear();
        dense_.clear();
        data_.clear();
    }

private:
    static uint32_t sparseEntryToIndex(Entity e) {
        return static_cast<uint32_t>(e);
    }

    std::vector<Entity> sparse_;
    std::vector<Entity> dense_;
    std::vector<T> data_;
};
