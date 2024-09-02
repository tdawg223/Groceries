#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "split.h"
#include <bits/stdc++.h>
#include <cassert>
#include <list>
#include <algorithm>
#include <format>
using namespace std;

vector<string> item_nums;
vector<string>customer_text;
vector<string> quantities;
void read_customers(string customer_file){
    ifstream customer_list(customer_file); 
    string customer_words;
    
    while(getline(customer_list,customer_words)){
        vector<string> split_elems = split(customer_words, ',');
        for(auto elem: split_elems){
            customer_text.push_back(elem);
        }
    }
}

vector<string>item_text;
void read_items(string customer_item_file){
    string item_words;
    ifstream item_file(customer_item_file);
    
    while(getline(item_file, item_words)){
        
        vector<string> split_elems = split(item_words, ',');
        for(auto elem: split_elems){
            item_text.push_back(elem);
        }
    
    }
    //for (auto elem: item_text){
        //cout << elem << endl;
    //}
    //ifstream fin(customer_item_file); 
    //string item_word;
    //while(fin >> item_word){
        //item_text.push_back(item_word);
    //}
    return;
}
    int find_cust_idx(int cust_id){
        for(int i = 0; i < customer_text.size(); i+=8){
            if(cust_id == stoi(customer_text.at(i))){
                return i;
            }
        }
        return -1;
    }
    int find_item_idx(int item_id){
        for (int i = 0; i < item_text.size(); i+=3){
            if (item_id == stoi(item_text.at(i))){
                return i;
            }
            
        }
        return -1;
    }

vector<string> item_Id;
vector<string> quantity;
//vector<string> price;
class LineItem{
    private:
        
    public:
        int item_id;
        //string description;
        double price;
        int item_quantity;
        //string id_placeholder;
       
        double sub_total(){
            int find_price = find_item_idx(item_id);
            price = stod(item_text[find_price + 2]);
            stringstream stream;
            stream << fixed << setprecision(2) << price;
            string z = stream.str();
            //double total = item_quantity * price;
            return price;
            
        }
        friend bool operator<(const LineItem& item1, const LineItem& item2) {
            return item1.item_id < item2.item_id;
        }
        LineItem(int id, int qty): item_id(id), item_quantity(qty){}

    
};
vector<LineItem> print_items; 
vector<string> payment_types;
vector<string> payment_codes;
vector<string> payment_dates;
vector<double> payment_amount;

class Payment{
    private:
    public:
        double amount;
        virtual string print_detail() const = 0;
};

class Credit: public Payment{
    private:
        
    public:
        string card_number;
        string expiration;
        Credit(string crd_num, string expir): card_number(crd_num), expiration(expir){}
        string print_detail() const override{
            string payment_string;
            payment_string += "Amount: $" + to_string(amount) + ", Paid by Credit Card " + card_number + ", " + "exp. " + expiration + '\n';
            cout << payment_string;
            return payment_string;
         }
};

class PayPal: public Payment{
    private:
        
    public:
        
        string pay_pal_ID;
        PayPal(string id_num): pay_pal_ID(id_num){}
         string print_detail() const override{
             string payment_string;
             payment_string += "Amount: $" + to_string(amount) +  ", Paid by PayPal ID: " + pay_pal_ID + '\n';
             cout << payment_string;
             return payment_string;
         }
};

class WireTransfer: public Payment{
    private:
        
    public:
        string bank_ID;
        string account_ID;
        WireTransfer(string id_num, string acc_id): bank_ID(id_num), account_ID(acc_id){}
         string print_detail() const override{
             string payment_string;
             payment_string += "Amount: $" + to_string(amount) + ", Paid by Wire transfer from " + bank_ID + ", " + "Acccount # " + account_ID + '\n';
             cout << payment_string;
             return payment_string;
         }
};


vector<string> customer_ID_nums;
vector<string> customer_order_nums;
vector<string> customer_order_dates;
class Customer{
    private:
        string customer_ID;
        string name;
        string street_address;
        string city;
        string state;
        string zip_code;
        string phone_number;
        string email_address;
    
        int customer_ID_conv;
        int street_address_conv;
    public:
    Customer(const vector<string>& vect){
        if (vect.size() >= 8) {
        for (int i = 0; i < vect.size(); i+=8){
            customer_ID = vect.at(i);
            customer_ID_conv = stoi(vect.at(i));
            name = vect.at(i+1);
            street_address = vect.at((i+2));
            street_address_conv = stoi(vect.at(i+2));
            city = vect.at(i+3);
            state = vect.at(i+4);
            zip_code = vect.at(i+5);
            phone_number = vect.at(i+6);
            email_address = vect.at(i+7);
        }
    }
    }
    void print_customer_info(const vector<string>& vect){
        for (int i = 0; i < vect.size(); i+=8){
            cout << "Email Address: " << vect.at(i+7) << endl;
        }
    }
    int set_cust_id(int id){
        customer_ID_conv = id;
        return customer_ID_conv;
    }
    int get_cust_id(){
        return customer_ID_conv;
    }
    string print_detail(){
         string customer_deets;
         int customer_info;
             //for(int i = 0; i < customer_order_nums.size(); i++){
                //customer_info = find_cust_idx(stoi(customer_ID_nums[0]));
             //customer_deets += "=====================\n";
                customer_deets += "Customer ID #" + customer_ID + "\n";
                customer_deets += name +',' + " ph. "+ phone_number +','+ " email: " + email_address +"\n";
                customer_deets += street_address + "\n";
                customer_deets += city + ", " + state + " "+ zip_code +'\n';
    
             //}
            //cout << customer_deets;
             
             return customer_deets;
    }
        
        //cout << customer_deets;
    int get_ID(){
        return customer_ID_conv;
    }
    string get_name(){
        return name;
    }
    int get_street_address(){
        return street_address_conv;
    }
    string get_city(){
        return city;
    }
    string get_state(){
        return state;
     }
    string get_zip_code(){
        return zip_code;
    }
    string get_phone_number(){
        return phone_number;
    }
    string get_email_address(){
        return email_address;
    }
};

class Item{
    private:
        string item_ID;
        string description;
        string price;
        int item_ID_to_int;
        double price_to_float;

    Item(const vector<string>& vect){
        for (int i = 0; i < vect.size(); i+=3){
            item_ID = vect.at(i);
            item_ID_to_int = stoi(vect.at(i));
        }
        for (int i = 0; i < vect.size(); i+= 3){
            description = vect.at(i + 1);
        }
        for (int i = 0; i < vect.size(); i+=3){
            price = vect.at(i+2);
            price_to_float = stod(vect.at(i+2));
        }
        if (vect.size() >= 3){
            description = vect.at(1);
            price = vect.at(2);
        
        //item_ID_to_int = stoi(vect.at(0));
            price_to_float = stod(vect.at(2));
        }

        }
        void print_item_info(const vector<string>& vect) {
        for (int i = 0; i < vect.size(); i+=3){
            cout << "price: " << vect.at(i + 2) << endl;  // Print item ID
        }
    }

};

            
    class Order{
    private:
        
        //vector<LineItem> line_items;
        
    public:
    Payment* payment = nullptr;
    string order_details;
        int cust_ID;
        int order_ID;
        string order_date;
        vector<LineItem> line_items;
        Order(){}
        string order_text = "";
        //Order(double payment);
        ~Order(){}
        string print_order(){

            order_details += "=====================================";
            order_details += "\n";
            order_details += "Order# " + to_string(order_ID) + ", Date: " + order_date + "\n\n";
            //order_details += "Amount: $" + " blank " + "\n\n";
            int cust_index = find_cust_idx(cust_ID);
            Customer customer_obj({customer_text.begin() + cust_index, customer_text.begin() + cust_index + 8});
            string customer_string = customer_obj.print_detail();
            order_details += customer_string += "\n";
            if (payment != nullptr){
                string payment_string = payment->print_detail();
                order_details += payment_string;
                delete payment;
            }
            //delete payment;
            
            //order_details += "Order detail:";
            //order_details += "\n";
            order_details += "Order Detail:";
            order_details += '\n';
            //int found_info = find_item_idx(line_items[0].item_id);
            for (int i = 0; i < line_items.size(); i++){
                Payment* payments;
                LineItem item(line_items[i].item_id, line_items[i].item_quantity);
                double price = item.sub_total();
                //payments 
                //total += price;
                stringstream stream;
                stream << fixed << setprecision(2) << price;
                string set_price = stream.str();
                sort(line_items.begin(), line_items.end());
                int found_info = find_item_idx(line_items[i].item_id);
                 order_details += "    Item " + to_string(line_items[i].item_id) + " " + item_text[found_info + 1] + ", " + to_string(line_items[i].item_quantity) + " @ " + set_price + "\n";
            }

            Customer customer(customer_text);

            order_details;
            cout << order_details;
                
        

            return order_details;
        }
                double total(){
                    
                    double complete_price = 0.0;
                    Payment* payments;
                    for (int i = 0; i < line_items.size(); i++){
                        LineItem item(line_items[i].item_id, line_items[i].item_quantity);
                        double price = item.sub_total() * item.item_quantity;
                        complete_price += price;
                    }
                    payments->amount = complete_price;
                    return complete_price;
                    
                }
        void add_line_item(LineItem& items){
            line_items.push_back(items);
        }
        
};
        
vector<string> item_Id_vect;
list<Order> orders;
void read_orders(string customer_order_file){
    string customer_ID;
    string customer_info;
    string customer_order_number;
    string customer_order_date;
    string item_ID_slasher;
    string item_ID_temp;
    string item_ID;
    string item_quantity;
    string payment_type;
    string payment_code;
    string payment_exp_date;
    vector<string> temp_item_Id_vect;
    vector<string> temp_payment_info;
    //vector<string> item_Id_vect;
    ifstream order_file(customer_order_file); 
         string order_words;
         //LineItem items;
    
    //int line_count = 0;
    while(getline(order_file, order_words)){
        Order order;
        vector<string> split_elems = split(order_words, ',');
        //vector<string> split_elems_at_slash = split(order_words, '-');
        //customer_ID += split_elems;
        temp_item_Id_vect.push_back(order_words);
        //customer_ID += split_elems[0];
        //customer_ID += '\n';
        // customer_order_number += split_elems[1];
        // customer_order_number += '\n';
        string id_conversion = split_elems[1];
        string cust_ID_conversion = split_elems[0];
        order.order_ID = stoi(id_conversion);
        order.order_date = split_elems[2];
        order.cust_ID = stoi(cust_ID_conversion);
        //customer_order_date += split_elems[2];
        //customer_order_date += '\n';
        vector<string> split_dash = split(split_elems[3], '-');
        //item_ID += split_dash[0];
        //item_quantity += split_dash[1];
        item_Id.push_back(split_dash[0]);
        quantity.push_back(split_dash[1]);
        //item_quantity += '\n';
        //item_ID += '\n';
        for (int i = 3; i < split_elems.size(); i++){
            vector<string> dash = split(split_elems[i], '-');
            LineItem items(stoi(dash[0]), stoi(dash[1]));
            order.line_items.push_back(items);
        }
        if(getline(order_file, order_words)){
            vector<string> split_elems2 = split(order_words, ',');
            //payment_type += split_elems2[0];
            //payment_type += '\n';
            //payment_code += split_elems2[1];
            //payment_code += '\n';
            //payment_exp_date += split_elems[2];
            //payment_exp_date += '\n';
            Payment* payments = nullptr;
            payment_types.push_back(split_elems2[0]);
            payment_codes.push_back(split_elems2[1]);
            //cout << payment_types[0];
            if(split_elems.size() <= 3){
                payment_dates.push_back(split_elems[2]);
            }
             //for (int i = 0; i < split_elems2[1].size(); i++){
             if(split_elems2.size() <= 3){
                if (stoi(split_elems2[0]) == 1){
                    //cout << split_elems2[2] << endl;
                    payments = new Credit(split_elems2[1], split_elems2[2]);
                    //Credit credits(split_elems2[1],split_elems2[2]);
                    //credit_payment_codes.push_back(split_elems2[1]);
                    //credits->card_number = split_elems2[1];
                    
                

                }
                else if(stoi(split_elems2[0]) == 2){
                    //cout << split_elems2[1] << endl;
                    payments = new PayPal(split_elems2[1]);
                    //paypal_payment_codes.push_back(split_elems2[1]);
                    
                
                }
                else if(stoi(split_elems2[0]) == 3){
                    //cout << split_elems2[2] << endl;
                    payments = new WireTransfer(split_elems2[1], split_elems2[2]);
                    //wire_transfer_payment_codes.push_back(split_elems2[1]);
                
            
                }
             }
             if (order_file.eof()) {
                break;
            }
            // }
            delete payments;
            payments = nullptr;
            
            orders.push_back(order);
        }
        

        
        }
        // item_Id.push_back(item_ID);
        // quantity.push_back(item_quantity);
        // customer_ID_nums.push_back(customer_ID);
        // customer_order_nums.push_back(customer_order_number);
        // customer_order_dates.push_back(customer_order_date);
        // payment_types.push_back(payment_type);
        // payment_codes.push_back(payment_code);
        // payment_dates.push_back(payment_exp_date);
        
        //for(auto& elem: customer_order_nums){
            //cout << elem;
        //}

        

  
        //cout << item_quantity;
        
        //  for(auto& elem: split_elems2){
        //      cout << elem  << endl;
        //  }

    //return;
    
}
           
int main() {
    read_customers("customers.txt"); // Step 1 above
    read_items("items.txt"); // Step 2 above
    read_orders("orders.txt");
    Order customer_order;
    //customer_order.print_order();
    //int find_ind = find_item_idx(23750);
    //cout << find_ind;
    //LineItem Item_obj;
    //string description = Item_obj.get_item_description();
    //cout << endl << "description: " << description;
    //Customer customer_obj(customer_text);
    //cout << Item_obj.get_price();
    //for (auto& Order: orders){
        //orders.print_order();
    // Payment* payment = nullptr;
    // payment->print_detail();
    //}
    ofstream ofs("order_report.txt");
    for ( auto customer_order: orders){
        ofs << customer_order.print_order() << endl;
    }
    
//one_customer_order(); // The rest of the steps
} // IMPORTANT NOTE. I NEED TO INITIALIZE THE CONSTRUCTORS