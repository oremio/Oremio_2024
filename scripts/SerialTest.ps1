# PowerShell Script to Configure COM Port and Open Terminal Window

# Set COM port configuration
$portName = "COM4"
$baudRate = 115200
$dataBits = 8
$stopBits = 1
$parity = "None" # 'None', 'Odd', 'Even', 'Mark', 'Space'
$flowControl = "None" # 'None', 'XonXoff', 'Hardware', 'Custom'

# Configure COM port
$port = [System.IO.Ports.SerialPort]::new($portName, $baudRate, [System.IO.Ports.Parity]::None, $dataBits, [System.IO.Ports.StopBits]::One)

# Open the COM port
try {
    $port.Open()
} catch {
    Write-Host "Error opening port: $_"
    exit
}

# Log file path
$logFile = "D:\SerialOutput\serial_output.log"

try {
    while ($port.IsOpen) {
        # 内部循环，用于持续读取串口数据
        while (-not [console]::KeyAvailable) {
            if ($port.BytesToRead -gt 0) {
                try {
                    $data = $port.ReadExisting()
                    Add-Content -Path $logFile -Value $data
                    Write-Host -NoNewline $data
                } catch {
                    Write-Host "Error reading from port: $_"
                }
            }
            Start-Sleep -Milliseconds 100
        }

        # 收到用户输入，处理输入
        $key = [console]::ReadKey($true)
        if ($key.Key -eq 'Enter') {
            $input = Read-Host "Enter command (type 'exit' to quit)"

            if ($input -eq 'exit') {
                break
            }

            try {
                $port.WriteLine($input)  # 自动添加换行符
                # 或者使用 $port.Write($input) 发送原始数据
            } catch {
                Write-Host "Error writing to port: $_"
            }
        }
    }
} catch {
    Write-Host "Error: $_"
} finally {
    if ($port.IsOpen) {
        $port.Close()
    }
    Write-Host "Port closed."
}
