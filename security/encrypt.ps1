# Generate a 256-bit AES key (32 bytes)
$key = New-Object byte[] 32
(New-Object Security.Cryptography.RNGCryptoServiceProvider).GetBytes($key)

# Generate a 128-bit IV (16 bytes)
$iv = New-Object byte[] 16
(New-Object Security.Cryptography.RNGCryptoServiceProvider).GetBytes($iv)

# Define the plaintext message
$plainText = "Top secret message."
$plainBytes = [System.Text.Encoding]::UTF8.GetBytes($plainText)

# Create AES encryptor
$aes = [System.Security.Cryptography.Aes]::Create()
$aes.Key = $key
$aes.IV = $iv

# Encrypt
$encryptor = $aes.CreateEncryptor()
$encryptedBytes = $encryptor.TransformFinalBlock($plainBytes, 0, $plainBytes.Length)
$encryptedBase64 = [Convert]::ToBase64String($encryptedBytes)

Write-Output "`nEncrypted (Base64):"
Write-Output $encryptedBase64

# Decrypt
$decryptor = $aes.CreateDecryptor()
$decryptedBytes = $decryptor.TransformFinalBlock($encryptedBytes, 0, $encryptedBytes.Length)
$decryptedText = [System.Text.Encoding]::UTF8.GetString($decryptedBytes)

Write-Output "`nDecrypted:"
Write-Output $decryptedText
