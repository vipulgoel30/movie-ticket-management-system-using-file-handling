#include <stdio.h>
#include <string.h>

int passwordValidator(char password[21])
{
  int upper = 0;
  int special = 0;
  int lower = 0;
  int i = 0;
  while (password[i] != '\0')
  {
    if (password[i] >= 'A' && password[i] <= 'Z')
      upper = 1;
    else if (password[i] >= 'a' && password[i] <= 'z')
      lower = 1;
    else if ((password[i] >= ' ' && password[i] <= '/') || (password[i] >= ':' && password[i] <= '@') || (password[i] >= '[' && password[i] <= '`') || (password[i] >= '}' && password[i] <= '~'))
      special = 1;
    if (lower && upper && special)
      return 1;
    i++;
  }
  return 0;
}

int checkUserExist(char phoneNo[11], int userType)
{
  FILE *fp;
  if (userType == 1)
    fp = fopen("./data/user.txt", "r");
  else
    fp = fopen("./data/admin.txt", "r");
  if (fp == NULL)
  {
    printf("Internal error\n");
    return 501;
  }
  while (!feof(fp))
  {
    char tempPhone[11] = "";
    char data[201] = "";
    fgets(data, 200, fp);
    for (int i = 0; i < 10; i++)
      tempPhone[i] = data[i];

    if (strcmp(tempPhone, phoneNo) == 0)
    {
      fclose(fp);
      return 1;
    }
  }
  fclose(fp);
  return 0;
}

int phoneNoInput(char phoneNo[11], int choice, int userType)
{
  strcpy(phoneNo, "");
  do
  {
    if (strlen(phoneNo) != 0)
      printf("Please enter the valid phone no.\n");
    printf("Enter the phone no : ");
    scanf("%s", phoneNo);
    int userValidation = checkUserExist(phoneNo, userType);
    // printf("%d", userValidation);
    if (userValidation == 501)
      return 1;

    if ((choice == 0 && userValidation == 1) || (choice == 1 && userValidation == 0))
    {
      strcpy(phoneNo, "");
      choice ? printf("User don't exists!\n") : printf("User already exists\n");
    }
  } while (strlen(phoneNo) != 10);
}

void passwordInput(char password[21])
{
  strcpy(password, "");
  do
  {
    if (strlen(password) != 0)
      printf("Enter the valid password!\n");
    printf("Enter the password( Min 8 characters ) : ");
    scanf("%s", password);
    if (!passwordValidator(password))
    {
      strcpy(password, "");
      printf("Password format - min 8 characters,1 lowercase char, 1 uppercase char, 1 special char\n");
    }
  } while (strlen(password) < 8);
}

int userValidator(char phoneNo[11], char password[21], int userType)
{

  FILE *fp;
  if (userType == 1)
    fp = fopen("./data/user.txt", "r");
  else
    fp = fopen("./data/admin.txt", "r");
  if (fp == NULL)
  {
    printf("Internal error!\n");
    return 501;
  }
  while (!feof(fp))
  {
    char data[200];
    fgets(data, 200, fp);
    char tempPhone[11] = "";
    for (int i = 0; i < 10; i++)
      tempPhone[i] = data[i];
    // printf("%s\n", tempPhone);

    if (strcmp(tempPhone, phoneNo) == 0)
    {
      printf("User exists inside\n");
      int i = 11;
      char tempPassword[21] = "";
      while (data[i] != '|')
      {
        tempPassword[i - 11] = data[i];
        i++;
      }
      printf("%s", tempPassword);
      if (!strcmp(password, tempPassword))
      {
        fclose(fp);
        return 1;
      }
    }
  }
  fclose(fp);
  return 0;
}