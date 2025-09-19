# Тестирование VFS
echo "=== VFS Testing ==="
echo "Loading VFS from: ./test_vfs"

# Навигация по VFS
echo "Current directory:"
pwd

echo "Listing root:"
ls /

echo "Changing to folder1:"
cd folder1
ls

echo "Changing to subfolder:"
cd ../folder2/subfolder
ls

echo "Reading files:"
cat ../file2.txt
cat file3.txt

echo "Testing error handling:"
cd /non_existent_folder
cat non_existent_file.txt

echo "=== VFS Test Complete ==="