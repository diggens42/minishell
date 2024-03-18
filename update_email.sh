#!/bin/bash

# Define the old and new email addresses
OLD_EMAIL="mott@2-F-6.42heilbronn.de"
NEW_EMAIL="mott@student.heilbronn.de"

# Use git filter-repo to update the email address, including the --force option
git filter-repo --commit-callback '
  if commit.author_email == b"'$OLD_EMAIL'":
    commit.author_email = b"'$NEW_EMAIL'"
  if commit.committer_email == b"'$OLD_EMAIL'":
    commit.committer_email = b"'$NEW_EMAIL'"
' --force

echo "Email addresses in commit history have been updated."
