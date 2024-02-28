# ved_gen
# Simple Web Application for Exam Records
#### Video Demo:  https://youtu.be/TXmO_qDm2HE
#### Description:
This web application serves the primary function of uploading examination records in XLSX format for subsequent processing and evaluation of exam results. It offers features for viewing exam lists, study groups, and uploaded results. Additionally, the admin can add new users, while the standard user can only access their relevant exam records.

Key features of this application include:

Uploading and downloading examination records in XLSX format
Listing and viewing exams, study groups, and uploaded results
Providing secure access for users based on their role (admin or user)
Restricting admin privileges to adding new users only
On the main page, users can view the list of exams. By clicking on a specific exam, users can view the list of the study group and the uploaded results. Additionally, they can download the XLSX file for filling in the results.

The application offers two user roles: admin and user. Only the admin can add new users, while both admin and user can access their relevant exam records.

In terms of security, this application utilizes authentication and authorization mechanisms to ensure that users can only access their relevant exam records. Additionally, all user data and actions are logged for auditing purposes.

This web application can be expanded further to include features such as result tracking, notification alerts, and data analytics.

#### Technologies Used:
This project is built using the following technologies:
- Flask: A lightweight WSGI web application framework.
- Jinja: A modern and designer-friendly templating language for Python.
- HTML/CSS: For structuring and styling the web pages.
- Bootstrap: A free and open-source CSS framework for responsive, mobile-first front-end web development.
- SQLite: A C library that provides a lightweight disk-based database.

#### Author: Anton Shtern
#### Location: Yaroslavl, Russia


# app.py

This is the main application file for the Flask web application. It sets up the application, configures the session, and defines the routes for the application.

## Key Components:

- **Imports**: The necessary modules and functions are imported at the beginning of the file.

- **Database Setup**: A connection to the SQLite database `vedDB.db` is established using the `SQL` class from the `sql` module.

- **Flask Application Setup**: A Flask application instance is created and configured. A custom filter `hrs` is added to the Jinja environment.

- **Session Configuration**: The Flask session is configured to use the filesystem.

- **Routes**: The file defines several routes for the application, including:
  - `@app.route("/")`: The main page route. It shows a list of exam templates and for each template, it also shows a list of students.
  - `@app.route("/vedomost")`: This route handles the display and download of specific exam templates.
  - `@app.route("/upload")`: This route handles the uploading of exam results in XLSX format.
  - `@app.route("/history")`: This route displays the history of uploaded exam results.
  - `@app.route("/login")`: This route handles user login.
  - `@app.route("/logout")`: This route handles user logout.
  - `@app.route("/register")`: This route handles user registration. Only admins can access this route.

- **Helper Functions**: The file uses several helper functions from the `helpers` module for tasks such as error handling, formatting, and user authentication.


# database.py

This file contains functions for interacting with the SQLite database `vedDB.db`. It uses the `SQL` class from the `sql` module to establish a connection to the database and execute SQL queries.

## Key Functions:

- `get_vedomosti(id=None, page=None)`: Retrieves examination records from the database. It can fetch records based on a specific ID or a page number for pagination.
- `get_vedomosti_pages()`: Calculates the total number of pages for the examination records.
- `get_students(ved_id=None)`: Retrieves student records associated with a specific examination record.
- `get_sprav_result()`: Retrieves the result reference data from the database.
- `update_result(ved_id=None, stud_id=None, result=None)`: Updates the result of a student for a specific examination record.
- `get_history()`: Retrieves the history of uploaded exam results.
- `update_history(action, details, dt)`: Updates the history of uploaded exam results.

# helpers.py

This file contains helper functions used throughout the application for tasks such as error handling, formatting, and user authentication.

## Key Functions:

- `apology(message, code=400)`: Renders an apology message to the user.
- `login_required(f)`: A decorator to ensure that a route requires user login.
- `admin_required(f)`: A decorator to ensure that a route requires admin access.
- `format_hrs(value)`: Formats a value as hours.
- `weak_password(password)`: Checks if a password is weak based on certain criteria.

# xlsxhelper.py

This file contains functions for handling XLSX files, specifically for generating and uploading examination records in XLSX format.

## Key Functions:

- `generate_xlsx_ved(id)`: Generates an XLSX file for a specific examination record.
- `upload_xlsx_ved(file)`: Uploads an XLSX file containing examination results to the application.
