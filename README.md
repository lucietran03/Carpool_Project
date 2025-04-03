# 🚗 **Carpooling Application**

This project is a **Carpooling Application** designed as part of an assignment for the courses **EEET2482/EEET2653**. The application facilitates carpooling services, allowing users to register as passengers, drivers, or admins, and interact with the system to manage carpools, requests, and ratings.  

## 🛠️ Key Features  

### 👥 User Roles  
- **Admin**:  
    - 👀 Can view all users and carpools.  
    - ✅ Can verify users.  
- **Driver**:  
    - ➕ Can create, view, and manage carpools.  
    - ✔️ Can accept or reject booking requests.  
    - 🌟 Can rate passengers.  
- **Passenger**:  
    - 🔍 Can search and book carpools.  
    - ❌ Can cancel bookings.  
    - 🌟 Can rate carpools.  

### 🚙 Carpool Management  
- Drivers can create carpools by specifying details such as departure, destination, time, date, car model, color, plate number, available seats, and minimum passenger rating.  
- Passengers can view available carpools and book them based on their preferences.  

### 📝 Request Management  
- Passengers can send booking requests to drivers.  
- Drivers can accept or reject these requests.  
- Requests are tracked with statuses like `PENDING`, `ACCEPTED`, `REJECTED`, or `CANCELLED`.  

### ⭐ Rating System  
- Passengers can rate carpools after completion.  
- Drivers can rate passengers.  
- Ratings are stored and used to calculate average scores for users and carpools.  

### 💾 File Management  
- Data is persisted in text files (`User.txt`, `Carpool.txt`, `Request.txt`, `Rating.txt`) to ensure the application retains information across sessions.  
- The `FileSaving` class handles loading and saving data to these files.  

### 🌍 City-Specific Locations  
- The application supports two cities: **Saigon** and **Hanoi**.  
- Users can select departure and destination locations specific to their city.  

### 📝 User Registration and Login  
- Users can register with details like username, password, full name, phone number, email, city, and ID type.  
- Users can log in based on their role (Admin, Passenger, or Driver).  

### 📊 Dashboards  
- Separate dashboards for Admins, Drivers, and Passengers to manage their respective functionalities.  

## 🔧 How It Works  

### 🏠 Main Menu  
- Users can log in as a **Guest**, **Admin**, **Passenger**, or **Driver**.  
- Guests can view available carpools or register as a user.  

### 👨‍💼 Admin Dashboard  
- Admins can view all users and carpools.  
- Admins can verify unverified users.  

### 🧳 Passenger Dashboard  
- Passengers can view available carpools, book carpools, cancel bookings, and rate carpools.  

### 🚗 Driver Dashboard  
- Drivers can create carpools, view their carpools, accept/reject booking requests, and rate passengers.  

### 💾 Data Persistence  
- All data is saved to text files, ensuring that user information, carpools, requests, and ratings are retained across sessions.  

## 🖥️ Technologies Used  
- **Programming Language**: C++  
- **Development Environment**: Visual Studio Code  
- **File Handling**: Text files for data storage  
- **Object-Oriented Programming**: Classes and inheritance for modular design  

## 💡 Potential Use Cases  
- A carpooling service for university students or employees.  
- A platform for managing shared rides in specific cities.  
- A learning project to demonstrate object-oriented programming and file handling in C++.  

This project demonstrates a comprehensive implementation of a carpooling system with a focus on modularity, user roles, and data persistence.  
## 📌 Note  

This project was initially developed as part of a course at **RMIT University** and serves as a foundation for a more professional carpooling application. While the current implementation covers essential features, there is significant potential for improvement and expansion to enhance functionality, scalability, and user experience.  
