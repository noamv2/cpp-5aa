#include <vector>
#include <iterator>
#include "doctest.h"
#include "OrgChart.hpp"

using namespace ariel;


TEST_CASE("Legal cases, with different data types"){

    SUBCASE(" T = String"){
    OrgChart Csuite; // The organization from the demo
      Csuite.add_root("CEO")
      .add_sub("CEO", "CTO")       
      .add_sub("CEO", "CFO")   
      .add_sub("CEO", "COO")   
      .add_sub("CTO", "VP_SW")
      .add_sub("COO", "VP_BI")
      .add_sub("CFO","VP_FI")
      .add_sub("CTO","CIO");

    /*
                    CEO
                   / | \
                  /  |  \
               CTO  CFO  COO
              / |    |     \
             /  |    |      \
       VP_SW  CIO  VP_FI    VP_BI
    */


   std::cout<<Csuite;
    std::vector<std::string> pre {"CEO", "CTO", "VP_SW", "CIO", "CFO", "VP_FI", "COO", "VP_BI"};
    std::vector<std::string> level {"CEO",  "CTO", "CFO", "COO",  "VP_SW", "CIO", "VP_FI", "VP_BI"};
    auto it = pre.begin();
    for(auto pre_it = Csuite.begin_preorder(); pre_it != Csuite.end_preorder(); ++pre_it ){
        
        CHECK(*pre_it == *it);
        it++;
    }
    it = level.begin();
    for(auto level_it = Csuite.begin_level_order(); level_it !=Csuite.end_level_order(); ++level_it ){
        CHECK(*level_it == *it);
        it++;
    }
    OrgChart o2;
      o2.add_root("1")
      .add_sub("1", "2")         
      .add_sub("1", "3")      
      .add_sub("2", "4")  
      .add_sub("2", "5"); 
    
    
    std::vector<std::string> nums{"1", "2" ,"3", "4", "5"};
    std::vector<std::string> reverse_nums{"4", "5" ,"2", "3", "1"};
    auto it4 = nums.begin();
    for(auto itr = o2.begin_level_order(); itr != o2.end_level_order(); ++itr){

        CHECK(*it4 == *itr);
        if(*it4 == "5"){
            it4++;
            continue;
        }
        it4++;
    }

    auto it5 = reverse_nums.begin();
    for(auto itr = o2.begin_reverse_order(); itr != o2.end_reverse_order(); ++itr){

        CHECK(*it5 == *itr);
        it5++;
    }
    }

    SUBCASE("T = int"){

    OrgChart<int> o;
    CHECK_NOTHROW(
      o.add_root(1)
      .add_sub(1, 2) 
      .add_sub(1, 3)
      .add_sub(2, 4)
      .add_sub(2, 5)
      .add_sub(3, 6)
      .add_sub(6,7)
      .add_sub(6,8));      

    /*       1
            / \
           /   \
          2     3
         / \     \
        4  5      6
                 / \
                7   8

    */
    std::vector<int> pre1 {1,2,4,5,3,6, 7, 8};
    std::vector<int> level1 {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> reverse1 {7, 8, 4, 5, 6, 2, 3, 1};

    auto it1 = pre1.begin();
    auto it2 = level1.begin();
    auto it3 = reverse1.begin();


    for(auto it= o.begin_preorder(); it != o.end_preorder(); ++it){
        CHECK(*it == *it1++);
    }
    for(auto it= o.begin_level_order(); it != o.end_level_order(); ++it){
        CHECK(*it == *it2++);
    }
    for(auto it= o.begin_reverse_order(); it != o.end_reverse_order(); ++it){
        CHECK(*it == *it3++);
        }
    }

}

// TEST_CASE("Merging of existing trees"){

//     OrgChart<int> o;
//     CHECK_NOTHROW(
//       o.add_root(1)
//       .add_sub(1, 2) 
//       .add_sub(1, 3)
//       .add_sub(2, 4)
//       .add_sub(2, 5)
//       .add_sub(3, 6)
//       .add_sub(6,7)
//       .add_sub(6,8));      

//     /*       1
//             / \
//            /   \
//           2     3
//          / \     \
//         4  5      6
//                  / \
//                 7   8

//     */


//    OrgChart<int> o2;
//    CHECK_NOTHROW(o2.add_root(10)
//    .add_sub(10,11)
//    .add_sub(10,12)
//    .add_sub(10,13)
//    .add_sub(12,14));

// /*
//             10
//            / | \
//           /  |  \
//         11  12  13
//              |
//             14
// */
//     CHECK_NOTHROW(o.add_sub(8,o2));
//     /*       1
//             / \
//            /   \
//           2     3
//          / \     \
//         4  5      6
//                  / \
//                 7   8
//                     |
//                    10
//                   / | \
//                  /  |  \
//                11  12  13
//                     |
//                    14
//     */

//     std::vector<int> pre1 {1,2,4,5,3,6, 7, 8, 10, 11, 12, 14, 13};
//     std::vector<int> level1 {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14};
//     std::vector<int> reverse1 {14, 11, 12, 13, 10, 7, 8, 4, 5, 6, 2, 3, 1};

//     auto it1 = pre1.begin();
//     auto it2 = level1.begin();
//     auto it3 = reverse1.begin();

//     std::cout<<o;
//     for(auto it= o.begin_preorder(); it != o.end_preorder(); ++it){
//         CHECK(*it == *it1++);
//     }
//     for(auto it= o.begin_level_order(); it != o.end_level_order(); ++it){
//         CHECK(*it == *it2++);
//     }
//     for(auto it= o.begin_reverse_order(); it != o.end_reverse_order(); ++it){
//         CHECK(*it == *it3++);
//         }
    
// }


TEST_CASE("Utilities"){


    OrgChart og;
    //Adding sub when tree is empty
    CHECK_THROWS(og.add_sub("CEO", "Joe"));
    CHECK_THROWS(og.add_sub("joe", "2"));

    //Changing root name
    CHECK_NOTHROW(og.add_root("CEO"));
    CHECK(*(og.begin_level_order()) == "CEO");

    CHECK_NOTHROW(og.add_root("Dan"));
    CHECK(*(og.begin_level_order()) == "Dan");    

    //Adding sub to non existsing node
    CHECK_THROWS(og.add_sub("CEO", "Joe"));
    CHECK_THROWS(og.add_sub("123", "Joe"));


    //Make sure begin() and end() implemented correctly as Level order traversal
    OrgChart<int> o;
    CHECK_NOTHROW(
      o.add_root(1)
      .add_sub(1, 2) 
      .add_sub(1, 3)
      .add_sub(2, 4)
      .add_sub(2, 5)
      .add_sub(3, 6)
      .add_sub(6,7)
      .add_sub(6,8));    

      std::vector<int> level {1, 2, 3, 4, 5, 6, 7, 8};
      auto it = level.begin();
      for(auto val: o){
          CHECK_EQ(val, *it++);
      }

      OrgChart strTree;
      strTree.add_root("root")
      .add_sub("root","child1")
      .add_sub("root","child2")
      .add_sub("root","child3");
      
      //Check for implementation of begin() and end()
      CHECK_NOTHROW(for(auto str: strTree));

      //Check arrow operator
      size_t combinedLen = 0;
      for(auto it = strTree.begin(); it != strTree.end(); ++it){

          combinedLen += it->length();
      }

      CHECK_EQ(combinedLen, 22);
      
}

