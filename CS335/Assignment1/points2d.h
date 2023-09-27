// --> Afnan Ebrahim
// Few comments describing the class Points2D:
// Points2D class acts as a storage for points. The class uses a pointer sequence which points to the beginning of a dynamically allocated array which each hold a "coordinate"
// of some sort. The class makes use of the big five, however defaults may not be used since were using dynamically allocated array which is pointed at by the data field
// sequence_. Therefore in order to prevent shallow copies, deep copies must be made.
//Points 2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>

#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

    // Place comments that provide a brief explanation of the class,
    // and its sample usage.
    template<typename Object>
    class Points2D {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation.

        // Zero-parameter constructor.
        // Set size to 0.
        // regular constructor creates a Points2D object of size 0: sequence_ is temporarily set to nullptr;
        Points2D()
        {
            sequence_ = nullptr;
            size_ = 0;
        }

        // Copy-constructor.
        // Copy-constructor - creates a copy of the Points2D object that it is placed in the parameters. Instead of simply setting sequence_= rhs.sequence, which 
        // would copy the pointer however when the rhs object is being destroyed the same object would be called by two separate pointers. The following implementation
        // prevents shallow copy and creates a deep copy of rhs.
        Points2D(const Points2D& rhs)
        {
            sequence_ = new std::array<Object, 2>[rhs.size()];
            for (size_t i = 0; i < rhs.size(); i++)
            {
                for (size_t j = 0; j < 2; j++)
                {
                    sequence_[i][j] = rhs.sequence_[i][j];
                }
            }
            size_ = rhs.size();
        }

        // Copy-assignment. If you have already written
        // the copy-constructor and the move-constructor
        // you can just use:
        // {
        // Points2D copy = rhs;
        // std::swap(*this, copy);
        // return *this;
        // }

        /*assignment operator takes the rhs objectand calls the copy constructorand makes a copy of the rhs object.the current object is then swapped with the copy of
        the rhs object.*/
        Points2D& operator=(const Points2D& rhs)
        {
            Points2D copy(rhs);
            std::swap(*this, copy);
            return *this;
        }

        // Move-constructor.
        /* moves rhs to current object and sets rhs.sequence_ to nullptr and size 0. */
        Points2D(Points2D&& rhs) : sequence_{ rhs.sequence_ }, size_{ rhs.size_ }
        {
            rhs.sequence_ = nullptr;
            rhs.size_ = 0;
        }

        // Move-assignment.
        // Just use std::swap() for all variables.
        /*swaps the object values and data, so datafields basically get swapped with one another.*/
        Points2D& operator=(Points2D&& rhs)
        {
            std::swap(sequence_, rhs.sequence_);
            std::swap(size_, rhs.size_);
            return *this;
        }
        /*deletes the dynamically allocated array that is pointed to by sequence_*/
        ~Points2D()
        {
            delete[] sequence_;
        }

        // End of big-five.

        // One parameter constructor.
        /*creates a single dynamically allocated point, which is pointed to by sequence_. Since theres only one array of size 2, size is set to 1 and the points values
        of item are transfered into dynamically allocated array one by one.*/
        Points2D(const std::array<Object, 2>& item) {
            // Provide code.
            sequence_ = new std::array<Object, 2>[1];

            sequence_[0][0] = item[0];
            sequence_[0][1] = item[1];
            size_ = 1;
        }
        /*returns the size of Points2D object*/
        size_t size() const {
            return size_;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.
        const std::array<Object, 2>& operator[](size_t location) const {
            // Code missing.
            if (size() <= location)
            {
                std::cerr << "ERROR\n";
                abort();
            }

            return sequence_[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        /* by comparing the size of each Points2D object using if statements, I created a new object with the same size of the larger object of the two. added 
        the elements of the points in each object. When one is smaller than the other, the extra points that aren't added with anything are simply transfered into 
        the new Points2D object which then returned.*/
        friend Points2D operator+(const Points2D& c1, const Points2D& c2)
        {
            // Code missing.
            Points2D <Object> c3;

            if (c1.size() == c2.size())
            {
                c3.sequence_ = new std::array<Object, 2>[c1.size()];
                c3.size_ = c1.size();
                for (size_t i = 0; i < c1.size(); i++)
                {
                    for (size_t j = 0; j < 2; j++)
                    {
                        c3.sequence_[i][j] = c1[i][j] + c2[i][j];
                    }
                }
            }
            else if (c1.size() < c2.size())
            {
                c3.sequence_ = new std::array<Object, 2>[c2.size()];
                c3.size_ = c2.size();
                for (size_t i = 0; i < c1.size(); i++)
                {
                    for (size_t j = 0; j < 2; j++)
                    {
                        c3.sequence_[i][j] = c1[i][j] + c2[i][j];
                    }
                }
                for (size_t i = c1.size(); i < c2.size(); i++)
                {
                    for (size_t j = 0; j < 2; j++)
                    {
                        c3.sequence_[i][j] = c2[i][j];
                    }
                }
            }
            else
            {
                c3.sequence_ = new std::array<Object, 2>[c1.size()];
                c3.size_ = c1.size();
                for (size_t i = 0; i < c2.size(); i++)
                {
                    for (size_t j = 0; j < 2; j++)
                    {
                        c3.sequence_[i][j] = c1[i][j] + c2[i][j];
                    }
                }
                for (size_t i = c2.size(); i < c1.size(); i++)
                {
                    for (size_t j = 0; j < 2; j++)
                    {
                        c3.sequence_[i][j] = c1[i][j];
                    }
                }
            }
            return c3;
        }

        // Overloading the << operator.
        /* the <<operator is overloaded so that when an Points2D object is printed each of the points that are stored are printed using paranthesis and commas.*/
        friend std::ostream& operator<<(std::ostream& out, const Points2D& some_points) {
            size_t pSize = some_points.size();
            if (pSize == 0)
            {
                out << "()\n";
                return out;
            }
            for (size_t i = 0; i < pSize; i++)
            {
                out << '(';
                for (size_t j = 0; j < 2; j++)
                {
                    out << some_points[i][j];
                    if (j == 0)
                        out << ", ";
                }
                if (i == (pSize - 1))
                {
                    out << ") \n";
                }
                else
                {
                    out << ") ";
                }
            }
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        /*pointes are taken straight from the input and then checked for proper type and then placed directly into dynamically allocated array which is 
        created for some_points object.*/
        friend std::istream& operator>>(std::istream& in, Points2D& some_points) {
            size_t inputed_size;

            in >> inputed_size;
            if (in.fail())
            {
                std::cerr << "ERROR\n";
                abort();
            }
            some_points.size_ = inputed_size;
            some_points.sequence_ = new std::array<Object, 2>[inputed_size];
            size_t counter = 0;
            std::string var;
            for (size_t i = 0; i < inputed_size; i++)
            {
                for (size_t j = 0; j < 2; j++)
                {
                    var = in.peek();
                    if (var == "")
                    {
                        std::cerr << "ERROR\n";
                        abort();
                    }
                    else
                        in >> some_points.sequence_[i][j];
                    if (in.fail())
                    {
                        std::cerr << "ERROR\n";
                        abort();
                    }
                    counter++;

                }
            }
            std::cout << '\n';
            if (counter != inputed_size * 2)
            {
                std::cerr << "ERROR\n";
                abort();
            }
            return in;

        }

    private:
        // Sequence of points.
        std::array<Object, 2>* sequence_;
        // Size of sequence.
        size_t size_;
    };


}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
