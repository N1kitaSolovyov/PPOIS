#pragma once
#ifndef ADVANCED_GRAPH_H
#define ADVANCED_GRAPH_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <unordered_map>
#include <string>
#include <sstream>
#include <functional>

class GraphException : public std::exception {
    std::string msg;
public:
    explicit GraphException(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

template<typename T>
struct TypeTraits {
    static std::string to_string(const T& value) {
        if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(value);
        }
        else {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
    }
};

template<>
struct TypeTraits<std::string> {
    static std::string to_string(const std::string& value) {
        return value;
    }
};

template<typename T>
struct WirthVertex;

template<typename T>
struct WirthEdge {
    std::shared_ptr<WirthVertex<T>> target;
    std::shared_ptr<WirthEdge<T>> next;
    explicit WirthEdge(std::shared_ptr<WirthVertex<T>> t) : target(t), next(nullptr) {}
};

template<typename T>
struct WirthVertex {
    T data;
    std::shared_ptr<WirthVertex<T>> next;
    std::weak_ptr<WirthVertex<T>> prev;
    std::shared_ptr<WirthEdge<T>> first_edge;
    explicit WirthVertex(const T& val) : data(val), next(nullptr), first_edge(nullptr) {}
};

template<typename T>
class VertexIterator {
    std::shared_ptr<WirthVertex<T>> current;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VertexIterator(std::shared_ptr<WirthVertex<T>> start = nullptr) : current(start) {}

    reference operator*() {
        if (!current) throw GraphException("Invalid iterator");
        return current->data;
    }

    pointer operator->() {
        if (!current) throw GraphException("Invalid iterator");
        return &current->data;
    }

    VertexIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    VertexIterator operator++(int) {
        VertexIterator temp = *this;
        ++(*this);
        return temp;
    }

    VertexIterator& operator--() {
        if (current && current->prev.lock()) {
            current = current->prev.lock();
        }
        return *this;
    }

    VertexIterator operator--(int) {
        VertexIterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const VertexIterator& other) const { return current == other.current; }
    bool operator!=(const VertexIterator& other) const { return !(*this == other); }
};

template<typename T>
class ConstVertexIterator {
    std::shared_ptr<WirthVertex<T>> current;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstVertexIterator(std::shared_ptr<WirthVertex<T>> start = nullptr) : current(start) {}

    reference operator*() {
        if (!current) throw GraphException("Invalid iterator");
        return current->data;
    }

    pointer operator->() {
        if (!current) throw GraphException("Invalid iterator");
        return &current->data;
    }

    ConstVertexIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    ConstVertexIterator operator++(int) {
        ConstVertexIterator temp = *this;
        ++(*this);
        return temp;
    }

    ConstVertexIterator& operator--() {
        if (current && current->prev.lock()) {
            current = current->prev.lock();
        }
        return *this;
    }

    ConstVertexIterator operator--(int) {
        ConstVertexIterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const ConstVertexIterator& other) const { return current == other.current; }
    bool operator!=(const ConstVertexIterator& other) const { return !(*this == other); }
};

template<typename T>
class AdjacentIterator {
    std::shared_ptr<WirthEdge<T>> current_edge;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    AdjacentIterator(std::shared_ptr<WirthEdge<T>> start = nullptr) : current_edge(start) {}

    reference operator*() {
        if (!current_edge) throw GraphException("Invalid iterator");
        return current_edge->target->data;
    }

    pointer operator->() {
        if (!current_edge) throw GraphException("Invalid iterator");
        return &current_edge->target->data;
    }

    AdjacentIterator& operator++() {
        if (current_edge) current_edge = current_edge->next;
        return *this;
    }

    AdjacentIterator operator++(int) {
        AdjacentIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const AdjacentIterator& other) const { return current_edge == other.current_edge; }
    bool operator!=(const AdjacentIterator& other) const { return !(*this == other); }
};

template<typename T, typename Traits = TypeTraits<T>>
class AdvancedWirthGraph {
private:
    std::shared_ptr<WirthVertex<T>> head_;
    std::shared_ptr<WirthVertex<T>> tail_;
    size_t vertex_count_;
    size_t edge_count_;
    std::unordered_map<T, std::shared_ptr<WirthVertex<T>>> vertex_map_;

    std::shared_ptr<WirthVertex<T>> find_vertex(const T& value) const {
        auto it = vertex_map_.find(value);
        return it != vertex_map_.end() ? it->second : nullptr;
    }

    bool has_edge_direct(std::shared_ptr<WirthVertex<T>> from, std::shared_ptr<WirthVertex<T>> to) const {
        auto edge = from->first_edge;
        while (edge) {
            if (edge->target == to) return true;
            edge = edge->next;
        }
        return false;
    }

    void add_edge_direction(std::shared_ptr<WirthVertex<T>> from, std::shared_ptr<WirthVertex<T>> to) {
        auto new_edge = std::make_shared<WirthEdge<T>>(to);
        new_edge->next = from->first_edge;
        from->first_edge = new_edge;
    }

    void remove_edge_direction(std::shared_ptr<WirthVertex<T>> from, std::shared_ptr<WirthVertex<T>> to) {
        std::shared_ptr<WirthEdge<T>> prev = nullptr;
        auto edge = from->first_edge;

        while (edge) {
            if (edge->target == to) {
                if (prev) {
                    prev->next = edge->next;
                }
                else {
                    from->first_edge = edge->next;
                }
                break;
            }
            prev = edge;
            edge = edge->next;
        }
    }

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using vertex_iterator = VertexIterator<T>;
    using const_vertex_iterator = ConstVertexIterator<T>;
    using adjacent_iterator = AdjacentIterator<T>;

    AdvancedWirthGraph() : head_(nullptr), tail_(nullptr), vertex_count_(0), edge_count_(0) {}

    AdvancedWirthGraph(const AdvancedWirthGraph& other)
        : head_(nullptr), tail_(nullptr), vertex_count_(0), edge_count_(0) {
        std::unordered_map<std::shared_ptr<WirthVertex<T>>, std::shared_ptr<WirthVertex<T>>> old_to_new;
        auto current = other.head_;

        while (current) {
            add_vertex(current->data);
            old_to_new[current] = tail_;
            current = current->next;
        }

        current = other.head_;
        while (current) {
            auto edge = current->first_edge;
            while (edge) {
                if (old_to_new[current]->data <= old_to_new[edge->target]->data) {
                    add_edge(old_to_new[current]->data, old_to_new[edge->target]->data);
                }
                edge = edge->next;
            }
            current = current->next;
        }
    }

    AdvancedWirthGraph(std::initializer_list<T> vertices,
        std::initializer_list<std::pair<T, T>> edges)
        : head_(nullptr), tail_(nullptr), vertex_count_(0), edge_count_(0) {
        for (const auto& v : vertices) add_vertex(v);
        for (const auto& e : edges) add_edge(e.first, e.second);
    }

    ~AdvancedWirthGraph() = default;

    AdvancedWirthGraph& operator=(const AdvancedWirthGraph& other) {
        if (this != &other) {
            AdvancedWirthGraph temp(other);
            swap(temp);
        }
        return *this;
    }

    void swap(AdvancedWirthGraph& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(vertex_count_, other.vertex_count_);
        std::swap(edge_count_, other.edge_count_);
        vertex_map_.swap(other.vertex_map_);
    }

    bool empty() const { return vertex_count_ == 0; }
    size_t size() const { return vertex_count_; }
    size_t max_size() const { return std::numeric_limits<size_t>::max(); }

    void clear() {
        head_ = tail_ = nullptr;
        vertex_count_ = edge_count_ = 0;
        vertex_map_.clear();
    }

    bool has_vertex(const T& value) const {
        return find_vertex(value) != nullptr;
    }

    bool has_edge(const T& u, const T& v) const {
        auto u_vert = find_vertex(u);
        auto v_vert = find_vertex(v);
        return u_vert && v_vert && has_edge_direct(u_vert, v_vert);
    }

    size_t vertex_count() const { return vertex_count_; }
    size_t edge_count() const { return edge_count_; }

    size_t vertex_degree(const T& value) const {
        auto vertex = find_vertex(value);
        if (!vertex) throw GraphException("Vertex not found: " + Traits::to_string(value));

        size_t degree = 0;
        auto edge = vertex->first_edge;
        while (edge) {
            degree++;
            edge = edge->next;
        }
        return degree;
    }

    void add_vertex(const T& value) {
        if (has_vertex(value)) {
            throw GraphException("Vertex already exists: " + Traits::to_string(value));
        }

        auto new_vertex = std::make_shared<WirthVertex<T>>(value);

        if (!head_) {
            head_ = tail_ = new_vertex;
        }
        else {
            tail_->next = new_vertex;
            new_vertex->prev = tail_;
            tail_ = new_vertex;
        }
        vertex_count_++;
        vertex_map_[value] = new_vertex;
    }

    void add_edge(const T& u, const T& v) {
        auto u_vert = find_vertex(u);
        auto v_vert = find_vertex(v);

        if (!u_vert) throw GraphException("Vertex not found: " + Traits::to_string(u));
        if (!v_vert) throw GraphException("Vertex not found: " + Traits::to_string(v));
        if (has_edge_direct(u_vert, v_vert)) {
            throw GraphException("Edge already exists: " + Traits::to_string(u) + "-" + Traits::to_string(v));
        }

        add_edge_direction(u_vert, v_vert);
        add_edge_direction(v_vert, u_vert);
        edge_count_++;
    }

    void remove_vertex(const T& value) {
        auto vertex = find_vertex(value);
        if (!vertex) throw GraphException("Vertex not found: " + Traits::to_string(value));

        std::vector<T> adjacent;
        auto edge = vertex->first_edge;
        while (edge) {
            adjacent.push_back(edge->target->data);
            edge = edge->next;
        }

        for (const auto& adj : adjacent) {
            remove_edge(value, adj);
        }

        if (vertex == head_) {
            head_ = vertex->next;
            if (head_) head_->prev.reset();
        }
        else {
            vertex->prev.lock()->next = vertex->next;
        }

        if (vertex == tail_) {
            tail_ = vertex->prev.lock();
            if (tail_) tail_->next = nullptr;
        }

        vertex_count_--;
        vertex_map_.erase(value);
    }

    void remove_edge(const T& u, const T& v) {
        auto u_vert = find_vertex(u);
        auto v_vert = find_vertex(v);

        if (!u_vert) throw GraphException("Vertex not found: " + Traits::to_string(u));
        if (!v_vert) throw GraphException("Vertex not found: " + Traits::to_string(v));
        if (!has_edge_direct(u_vert, v_vert)) {
            throw GraphException("Edge not found: " + Traits::to_string(u) + "-" + Traits::to_string(v));
        }

        remove_edge_direction(u_vert, v_vert);
        remove_edge_direction(v_vert, u_vert);
        edge_count_--;
    }

    vertex_iterator vertex_begin() { return vertex_iterator(head_); }
    vertex_iterator vertex_end() { return vertex_iterator(nullptr); }

    const_vertex_iterator vertex_begin() const { return const_vertex_iterator(head_); }
    const_vertex_iterator vertex_end() const { return const_vertex_iterator(nullptr); }

    const_vertex_iterator cvertex_begin() const { return const_vertex_iterator(head_); }
    const_vertex_iterator cvertex_end() const { return const_vertex_iterator(nullptr); }

    adjacent_iterator adjacent_begin(const T& value) {
        auto vertex = find_vertex(value);
        if (!vertex) throw GraphException("Vertex not found: " + Traits::to_string(value));
        return adjacent_iterator(vertex->first_edge);
    }

    adjacent_iterator adjacent_end(const T& value) {
        return adjacent_iterator(nullptr);
    }

    vertex_iterator begin() { return vertex_begin(); }
    vertex_iterator end() { return vertex_end(); }
    const_vertex_iterator begin() const { return vertex_begin(); }
    const_vertex_iterator end() const { return vertex_end(); }

    bool operator==(const AdvancedWirthGraph& other) const {
        if (vertex_count_ != other.vertex_count_ || edge_count_ != other.edge_count_)
            return false;

        for (const auto& v_pair : vertex_map_) {
            if (!other.has_vertex(v_pair.first)) return false;
        }

        for (const auto& v_pair : vertex_map_) {
            auto vertex = v_pair.second;
            auto edge = vertex->first_edge;
            while (edge) {
                if (vertex->data <= edge->target->data) {
                    if (!other.has_edge(vertex->data, edge->target->data)) return false;
                }
                edge = edge->next;
            }
        }
        return true;
    }

    bool operator!=(const AdvancedWirthGraph& other) const { return !(*this == other); }

    bool operator<(const AdvancedWirthGraph& other) const {
        return vertex_count_ < other.vertex_count_ ||
            (vertex_count_ == other.vertex_count_ && edge_count_ < other.edge_count_);
    }

    bool operator>(const AdvancedWirthGraph& other) const { return other < *this; }
    bool operator<=(const AdvancedWirthGraph& other) const { return !(other < *this); }
    bool operator>=(const AdvancedWirthGraph& other) const { return !(*this < other); }

    friend std::ostream& operator<<(std::ostream& os, const AdvancedWirthGraph& graph) {
        os << "Graph (Vertices: " << graph.vertex_count_ << ", Edges: " << graph.edge_count_ << ")\n";
        os << "Vertices: ";
        auto current = graph.head_;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        os << "\nEdges: ";
        current = graph.head_;
        while (current) {
            auto edge = current->first_edge;
            while (edge) {
                if (current->data <= edge->target->data) {
                    os << "(" << current->data << "-" << edge->target->data << ") ";
                }
                edge = edge->next;
            }
            current = current->next;
        }
        return os;
    }
};

#endif 