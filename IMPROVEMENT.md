1. Basic features almost work.
2. Additional features not fully implemented.
3. You should test your implementation more carefully, e.g.
    + No extra password policy implemented, e.g. consists of 1 uppercase, 1 lowercase.
    + Registration as admin will skip the confirmation code.
    + Profile is empty after the 1st login.
    + Frequent skipping of input, e.g. when changing password.
    + Change password failed.
    + Purchase credit should be accompanied with password to authenticate the transaction.
    + Credit is not returned to the passenger after driver rejected the booking.
    + No checking mechanism for rating score, i.e. user is able to type the score which is out of range.
    + The rating score for passenger should be from driver to passenger, and vice versa. There's no option to see the comments.
    + Etc.
4. Coding style: Some commented code could be removed from the code.
Overall, the user friendliness of the app needs to be improved.

=> This is what need to be improved after first test. After that, below are some things/improvements may be done.
1. Create more than 20 datas for each file.
2. Create more stricky error handling for each feature/attributes.
3. For carpool class:
    - The finding feature (typing word instead of number)
    - The constructor (can be reduced the number)
    - Can reference some of carpooling app in the world to improve the attributes.
    - Can combine with real-time for the related features.
4. For departure:
    - Can add more choices for user.
    - Open more big cities for user to register and use this app.
    - Improve the word searching instead of the number
5. For driver:
    - Fix the bug for all feature (There is no synchronization when changing data and must query again from the beginning.)
    - The rating feature is not working at all
6. For passenger:
    - Fix the rating feature
7. For user:
    - Check the register for error handling, improve the quality of attribute (ex: Password)
8. Should improve the login features
9. Check the simple interface
10. Some potential improvement:
    - Finish the back-end feature/data
    - Figma design can be considered
    - Using HTML-CSS-Javascripts for front-end coding